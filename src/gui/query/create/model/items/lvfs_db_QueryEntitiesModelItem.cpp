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

#include "lvfs_db_QueryEntitiesModelItem.h"
#include "../../../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

QueryEntitiesModelItem::QueryEntitiesModelItem(const Entity::Property &property, Model::Item *parent) :
    Model::Item(parent),
    m_property(property)
{}

QueryEntitiesModelItem::~QueryEntitiesModelItem()
{
    for (auto &i : m_items)
        delete i;
}

Model::Item *QueryEntitiesModelItem::at(size_type index) const
{
    return m_items[index];
}

QueryEntitiesModelItem::size_type QueryEntitiesModelItem::size() const
{
    return m_items.size();
}

QueryEntitiesModelItem::size_type QueryEntitiesModelItem::indexOf(Model::Item *item) const
{
    for (auto i = m_items.begin(); i != m_items.end(); ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

QVariant QueryEntitiesModelItem::data(qint32 column, qint32 role) const
{
    if (column == 0 && role == Qt::DisplayRole)
        return toUnicode(m_property.name);
    else
        return QVariant();
}

}}
