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
#include "items/lvfs_db_RootNodeRootItem.h"

#include <brolly/assert.h>


namespace LVFS {
namespace Db {

RootNode::RootNode(const Interface::Holder &container, const Interface::Holder &parent) :
    Core::Qt::BaseNode(parent),
    m_container(container),
    m_title(toUnicode(m_container.interface()->as<IEntry>()->title())),
    m_schema(toUnicode(m_container.interface()->as<IEntry>()->schema())),
    m_location(toUnicode(m_container.interface()->as<IEntry>()->location())),
    m_icon(),
    m_geometry(),
    m_sorting(0, ::Qt::AscendingOrder)
{
    ASSERT(m_container.isValid());
    ASSERT(m_sorting.first < columnCount(QModelIndex()));
    m_icon.addFile(toUnicode(m_container.interface()->as<IEntry>()->type()->icon()->as<IEntry>()->location()), QSize(16, 16));

    for (auto i : m_container->entities())
        doAdd(i.second);
}

RootNode::~RootNode()
{}

const QString &RootNode::title() const
{
    return m_title;
}

const QString &RootNode::schema() const
{
    return m_schema;
}

const QString &RootNode::location() const
{
    return m_location;
}

const Interface::Holder &RootNode::file() const
{
    return m_container.interface();
}

const Interface::Holder &RootNode::parent() const
{
    return Core::Node::parent();
}

const RootNode::Geometry &RootNode::geometry() const
{
    return m_geometry;
}

const RootNode::Sorting &RootNode::sorting() const
{
    return m_sorting;
}

void RootNode::refresh(int depth)
{}

void RootNode::opened(const Interface::Holder &view)
{
    return Core::Node::opened();
}

void RootNode::closed(const Interface::Holder &view)
{
    return Core::Node::closed();
}

Qt::ItemFlags RootNode::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QAbstractItemModel *RootNode::model() const
{
    return const_cast<RootNode *>(this);
}

QModelIndex RootNode::parentIndex() const
{
    return m_parentIndex;
}

void RootNode::setParentIndex(const QModelIndex &index)
{
    m_parentIndex = index;
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
        m_items.clear();
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
