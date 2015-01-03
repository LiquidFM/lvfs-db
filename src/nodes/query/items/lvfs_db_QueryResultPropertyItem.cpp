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

#include "lvfs_db_QueryResultPropertyItem.h"
#include "lvfs_db_QueryResultValueItem.h"
#include "../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

QueryResultPropertyItem::QueryResultPropertyItem(const Entity::Property &property, Item *parent) :
    QueryResultItem(parent),
    m_property(property)
{}

QueryResultPropertyItem::~QueryResultPropertyItem()
{
    for (auto i : m_items)
        delete i;
}

QueryResultPropertyItem::Item *QueryResultPropertyItem::at(size_type index) const
{
    return m_items.at(index);
}

QueryResultPropertyItem::size_type QueryResultPropertyItem::size() const
{
    return m_items.size();
}

QueryResultPropertyItem::size_type QueryResultPropertyItem::indexOf(Item *item) const
{
    for (auto i = m_items.begin(), end = m_items.end(); i != end; ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

QVariant QueryResultPropertyItem::data(qint32 column, qint32 role) const
{
    if (role == Qt::DisplayRole)
        return toUnicode(m_property.name);
    else
        return QVariant();
}

bool QueryResultPropertyItem::isRoot()
{
    return false;
}

bool QueryResultPropertyItem::isProperty()
{
    return true;
}

bool QueryResultPropertyItem::isValue()
{
    return false;
}

bool QueryResultPropertyItem::isPath()
{
    return false;
}

bool QueryResultPropertyItem::isRootPathValue()
{
    return false;
}

void QueryResultPropertyItem::add(const EntityValue &value)
{
    m_items.push_back(new QueryResultValueItem(value, this));
}

void QueryResultPropertyItem::add(const EntityValue::Values &values)
{
    for (auto i : values)
        m_items.push_back(new QueryResultValueItem(i.second, this));
}

void QueryResultPropertyItem::remove(size_type index)
{
    delete m_items.at(index);
    m_items.erase(m_items.begin() + index);
}

}}
