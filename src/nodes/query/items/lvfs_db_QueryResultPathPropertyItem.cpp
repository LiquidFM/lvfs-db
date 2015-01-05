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

#include "lvfs_db_QueryResultPathPropertyItem.h"
#include "lvfs_db_QueryResultRootPathValueItem.h"
#include <lvfs-core/models/Qt/SortFilterModel>


namespace LVFS {
namespace Db {

//inline static bool lessThan(const QueryResultItem::Holder &v1, const QueryResultItem::Holder &v2)
//{
//    return Core::Qt::SortFilterModel::compareByFileNames(v1.as<QueryResultRootPathValueItem>()->info(), v2.as<QueryResultRootPathValueItem>()->info());
//}


QueryResultPathPropertyItem::QueryResultPathPropertyItem(const Entity::Property &property, Item *parent) :
    QueryResultPropertyItem(property, parent)
{}

//void QueryResultPathPropertyItem::add(const IFileContainer *container, const EntityValue &value)
//{
//    m_items.push_back(Holder(new QueryResultRootPathValueItem(container, value, this)));
//    qSort(m_items.begin(), m_items.end(), lessThan);
//}
//
//void QueryResultPathPropertyItem::add(const IFileContainer *container, const EntityValue::List &values)
//{
//    for (auto i : values)
//        m_items.push_back(Holder(new QueryResultRootPathValueItem(container, i, this)));
//
//    qSort(m_items.begin(), m_items.end(), lessThan);
//}

void QueryResultPathPropertyItem::add(EFC::List<Interface::Holder> &files, const Interface::Adaptor<IStorage> &container, const EntityValue::Values &values)
{
    QueryResultRootPathValueItem *item;

    for (auto i : values)
    {
        m_items.push_back(item = new QueryResultRootPathValueItem(container, i.second, this));
//        files.add(item.as<QueryResultRootPathValueItem>()->location(), item);
    }

//    qSort(m_items.begin(), m_items.end(), lessThan);
}

}}
