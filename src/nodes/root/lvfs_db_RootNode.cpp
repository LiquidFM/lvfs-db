/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2015 Dmitriy Vilkov, <dav.daemon@gmail.com>
 *
 * lvfs-db is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lvfs-db is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lvfs-db. If not, see <http://www.gnu.org/licenses/>.
 */

#include "lvfs_db_RootNode.h"

#include "items/lvfs_db_RootNodePropertyItem.h"
#include "items/lvfs_db_RootNodeEntityItem.h"
#include "items/lvfs_db_RootNodeFilesItem.h"

#include "../query/lvfs_db_QueryResultsNode.h"
#include "../filesystem/lvfs_db_FileSystemDirectory.h"

#include "../../gui/value/lvfs_db_EntityValueDialog.h"
#include "../../gui/query/create/lvfs_db_CreateQueryDialog.h"
#include "../../lvfs_db_common.h"

#include <lvfs/IEntry>
#include <lvfs-core/IView>
#include <lvfs-core/INodeFactory>
#include <lvfs-core/models/Qt/IView>
#include <brolly/assert.h>

#include <QtGui/QMessageBox>


namespace LVFS {
namespace Db {

RootNode::RootNode(const Interface::Holder &container, const Interface::Holder &parent) :
    Complements(container, parent),
    m_container(container),
    m_geometry(),
    m_sorting(0, ::Qt::AscendingOrder)
{
    ASSERT(m_sorting.first < columnCount(QModelIndex()));
}

RootNode::~RootNode()
{
    ASSERT(m_items.empty());
}

void RootNode::refresh(int depth)
{
    if (m_items.empty())
    {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
        m_items.push_back(new RootNodeFilesItem());
        endInsertRows();

        for (auto i : m_container->entities())
            doAdd(i.second);
    }

    for (auto i : m_views)
        i->as<Core::Qt::IView>()->select(currentIndex());
}

void RootNode::opened(const Interface::Holder &view)
{
    m_views.insert(view);
}

void RootNode::closed(const Interface::Holder &view)
{
    m_views.erase(view);
}

Interface::Holder RootNode::accept(const Interface::Holder &view, Files &files)
{
    return Interface::Holder();
}

void RootNode::copy(const Interface::Holder &view, const Interface::Holder &dest, Files &files, bool move)
{
    ASSERT(!"Should not be reached!");
}

void RootNode::remove(const Interface::Holder &view, Files &files)
{

}

void RootNode::clear()
{
    if (!m_items.empty())
    {
        struct LocalDeleter
        {
            inline EFC::Vector<Item *>::iterator operator()(EFC::Vector<Item *> &container, EFC::Vector<Item *>::iterator &iterator) const
            { delete (*iterator); return container.erase(iterator); }
        };

        struct LocalAdaptor
        {
            inline const Interface::Holder &operator()(EFC::Vector<Item *>::iterator &iterator) const
            {
                if (static_cast<RootNodeItem *>(*iterator)->isFiles())
                    return static_cast<RootNodeFilesItem *>(*iterator)->node();

                return node;
            }

            Interface::Holder node;
        };

        beginRemoveRows(QModelIndex(), 0, m_items.size() - 1);
        Core::INode::clear(m_items, LocalAdaptor(), LocalDeleter());
        m_entities.clear();
        endRemoveRows();
    }
}

Interface::Holder RootNode::node(const Interface::Holder &file) const
{
    return Interface::Holder();
}

void RootNode::setNode(const Interface::Holder &file, const Interface::Holder &node)
{
    ASSERT(file.isValid());
}

Qt::ItemFlags RootNode::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QAbstractItemModel *RootNode::model() const
{
    return const_cast<RootNode *>(this);
}

const RootNode::Geometry &RootNode::geometry() const
{
    return m_geometry;
}

const RootNode::Sorting &RootNode::sorting() const
{
    return m_sorting;
}

QModelIndex RootNode::currentIndex() const
{
    return m_currentIndex;
}

void RootNode::setCurrentIndex(const QModelIndex &index)
{
    m_currentIndex = index;
}

Interface::Holder RootNode::activated(const Interface::Holder &view, const QModelIndex &index)
{
    RootNodeItem *item;

    if ((item = static_cast<RootNodeItem *>(index.internalPointer()))->isEntity())
        if (m_container->transaction())
        {
            EntityValueReader reader(m_container->entityValues(static_cast<RootNodeEntityItem *>(item)->entity()));
            EntityValueDialog dialog(m_container, reader, view->as<Core::IView>()->widget());

            if (dialog.exec() == EntityValueDialog::Accepted)
            {
                if (!m_container->commit())
                {
                    QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_container->lastError()));
                    m_container->rollback();
                }
            }
            else
                m_container->rollback();

            m_container->setListGeometry(static_cast<RootNodeEntityItem *>(item)->entity(), fromQRect(dialog.geometry()));
        }
        else
            QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_container->lastError()));
    else
        if (item->isFiles())
        {
            if (!static_cast<RootNodeFilesItem *>(item)->node().isValid())
            {
                Interface::Holder file(new (std::nothrow) FileSystemDirectory(m_container, m_container->file()));

                if (LIKELY(file.isValid()))
                    static_cast<RootNodeFilesItem *>(item)->setNode(file->as<Core::INodeFactory>()->createNode(file, Interface::Holder::fromRawData(this)));
            }

            return static_cast<RootNodeFilesItem *>(item)->node();
        }

    return Interface::Holder();
}

Interface::Holder RootNode::search(const Interface::Holder &view, const QModelIndex &index)
{
    if (static_cast<RootNodeItem *>(index.internalPointer())->isEntity())
    {
        RootNodeEntityItem *item = static_cast<RootNodeEntityItem *>(index.internalPointer());

        if (item->entity().type() == Entity::Composite)
            if (m_container->transaction())
            {
                CreateQueryDialog dialog(m_container, item->entity(), view->as<Core::IView>()->widget());

                if (dialog.exec() == CreateQueryDialog::Accepted)
                {
                    EntityValueReader reader(m_container->entityValues(dialog.entity(), dialog.constraint()->constraint()));

                    if (reader.isValid() && m_container->commit())
                        return Interface::Holder(new (std::nothrow) QueryResultsNode(m_container, reader, Interface::Holder::fromRawData(this)));
                    else
                    {
                        QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_container->lastError()));
                        m_container->rollback();
                    }
                }
                else
                    m_container->rollback();
            }
            else
                QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_container->lastError()));
    }

    return Interface::Holder();
}

void RootNode::insert(const Interface::Holder &view, const QModelIndex &index)
{

}

void RootNode::remove(const Interface::Holder &view, const QModelIndex &index)
{

}

RootNode::size_type RootNode::size() const
{
    return m_items.size();
}

RootNode::Item *RootNode::at(size_type index) const
{
    return m_items[index];
}

RootNode::size_type RootNode::indexOf(Item *item) const
{
    for (auto i = m_items.begin(), end = m_items.end(); i != end; ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

void RootNode::doAdd(const Entity &entity)
{
    RootNodeEntityItem *item;

    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.push_back(item = new RootNodeEntityItem(entity));
    m_entities[entity].push_back(item);
    expand(item);
    endInsertRows();
}

void RootNode::doRemove(const Entity &entity)
{
    size_type row;
    Item *parent;
    EFC::Vector<Item *> list = std::move(m_entities[entity]);
    QModelIndex index;

    for (auto i = list.begin(), end = list.end(); i != end; ++i)
    {
        index = Core::Tools::TreeModel::parent(*i, row);
        beginRemoveRows(index, row, row);

        if (parent = (*i)->parent())
            static_cast<RootNodeEntityItem *>(parent)->remove(row);
        else
        {
            delete m_items[row];
            m_items.erase(m_items.begin() + row);
        }

        endRemoveRows();
    }
}

void RootNode::doAdd(const QModelIndex &index, Item *item, const Entity &property, const EFC::String &propertyName)
{
    RootNodeEntityItem *child;

    beginInsertRows(index, static_cast<RootNodeEntityItem *>(item)->size(), static_cast<RootNodeEntityItem *>(item)->size());
    static_cast<RootNodeEntityItem *>(item)->add(child = new RootNodePropertyItem(property, propertyName, item));
    m_entities[property].push_back(child);
    expand(child);
    endInsertRows();
}

void RootNode::doRemove(const QModelIndex &index, Item *item, Item *property)
{
    Item::size_type idx = item->indexOf(property);

    beginRemoveRows(Core::Tools::TreeModel::parent(index), idx, idx);
    EFC::Vector<Item *> &items = m_entities[static_cast<RootNodeEntityItem *>(item)->entity()];

    for (auto i = items.begin(), end = items.end(); i != end; ++i)
        if (*i == item)
        {
            items.erase(i);
            break;
        }

    static_cast<RootNodeEntityItem *>(item)->remove(idx);
    endRemoveRows();
}

void RootNode::expand(Item *p)
{
    RootNodeEntityItem *item;
    RootNodeEntityItem *parent = static_cast<RootNodeEntityItem *>(p);

    for (auto i : parent->entity().properties())
    {
        parent->add(item = new RootNodePropertyItem(i.second, parent));
        m_entities[item->entity()].push_back(item);
        expand(item);
    }
}

}}
