/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2014 Dmitriy Vilkov, <dav.daemon@gmail.com>
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
#include "../../lvfs_db_common.h"
#include "../../gui/value/list/editable/lvfs_db_EditableValueListDialog.h"

#include <lvfs/IEntry>
#include <lvfs-core/models/Qt/IView>
#include <brolly/assert.h>

#include <QtGui/QMessageBox>


namespace LVFS {
namespace Db {

RootNode::RootNode(const Interface::Holder &container, const Interface::Holder &parent) :
    Core::Qt::BaseNode(parent),
    m_container(container),
    m_geometry(),
    m_sorting(0, ::Qt::AscendingOrder)
{
    ASSERT(m_container.isValid());
    ASSERT(m_sorting.first < columnCount(QModelIndex()));
}

RootNode::~RootNode()
{
    ASSERT(m_items.empty());
}

const Interface::Holder &RootNode::parent() const
{
    return Core::Node::parent();
}

const Interface::Holder &RootNode::file() const
{
    return m_container.interface();
}

void RootNode::refresh(int depth)
{
    if (m_items.empty())
        for (auto i : m_container->entities())
            doAdd(i.second);

    if (!m_items.empty())
        for (auto i : views())
            i->as<Core::Qt::IView>()->select(currentIndex());
}

void RootNode::incLinks(int count)
{
    Core::Node::incLinks(count);
}

void RootNode::decLinks(int count)
{
    Core::Node::decLinks(count);
}

void RootNode::opened(const Interface::Holder &view)
{
    Core::Node::opened(view);
}

void RootNode::closed(const Interface::Holder &view)
{
    Core::Node::closed(view);
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

Interface::Holder RootNode::activated(const QModelIndex &index, QWidget *parent)
{
    RootNodeItem *item;

    if ((item = static_cast<RootNodeItem *>(index.internalPointer()))->isEntity())
        if (m_container->transaction())
        {
            EntityValueReader reader(m_container->entityValues(static_cast<RootNodeEntityItem *>(item)->entity()));
            EditableValueListDialog dialog(m_container, reader, parent);

            if (dialog.exec() == EditableValueListDialog::Accepted)
            {
                if (!m_container->commit())
                {
                    QMessageBox::critical(parent, tr("Error"), toUnicode(m_container->lastError()));
                    m_container->rollback();
                }
            }
            else
                m_container->rollback();

            m_container->setListGeometry(static_cast<RootNodeEntityItem *>(item)->entity(), fromQRect(dialog.geometry()));
        }
        else
            QMessageBox::critical(parent, tr("Error"), toUnicode(m_container->lastError()));
//    else
//        if (item->isFiles())
//        {
//            if (static_cast<RootNodeFilesItem *>(item)->node() == NULL)
//            {
//                IFileContainer::Holder folder(m_container->container()->open());
//                Node *node = new FolderNode(folder, m_container, this);
//                static_cast<RootNodeFilesItem *>(item)->setNode(node);
//            }
//
//            return static_cast<RootNodeFilesItem *>(item)->node();
//        }

    return Interface::Holder();
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

void RootNode::removeChildren()
{
    if (!m_items.empty())
    {
        beginRemoveRows(QModelIndex(), 0, m_items.size() - 1);

        for (auto &i : m_items)
            delete i;

        m_items.clear();
        m_entities.clear();
        endRemoveRows();
    }
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
