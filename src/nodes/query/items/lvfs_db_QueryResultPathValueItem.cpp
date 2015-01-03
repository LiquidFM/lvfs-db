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

#include <lvfs-core/models/Qt/SortFilterModel>
#include "lvfs_db_QueryResultPathValueItem.h"


namespace LVFS {
namespace Db {

//inline static bool compareByFileNames(const QueryResultItem::Holder &v1, const QueryResultItem::Holder &v2)
//{
//    return Core::Qt::SortFilterModel::compareByFileNames(v1.as<QueryResultPathItem>()->info(), v2.as<QueryResultPathItem>()->info());
//}
//
//
//QueryResultPathValueItem::QueryResultPathValueItem(const IFileContainer *container, SnapshotItem *item, Item *parent) :
//    QueryResultPathItem(item->info(), parent),
//    m_container(container)
//{
//    if (m_info->isDir())
//    {
//        m_thisContainer = item->thisContainer().take();
//
//        for (SnapshotItem::const_iterator i = item->begin(), end = item->end(); i != end; ++i)
//            m_items.push_back(QueryResultItem::Holder(new QueryResultPathValueItem(m_thisContainer.data(), (*i), this)));
//    }
//
//    qSort(m_items.begin(), m_items.end(), compareByFileNames);
//}

bool QueryResultPathValueItem::isRootPathValue()
{
    return false;
}

void QueryResultPathValueItem::open() const
{
//    Application::open(m_container, info());
}

}}
