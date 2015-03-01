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

#include "lvfs_db_QueryResultRootPathValueItem.h"
#include "lvfs_db_QueryResultPathValueItem.h"
#include "../../../lvfs_db_common.h"

#include <lvfs/Module>
#include <lvfs/IApplication>
#include <lvfs/IApplications>
#include <lvfs-core/models/Qt/SortFilterModel>


namespace LVFS {
namespace Db {

//inline static bool compareByFileNames(const Item::Holder &v1, const Item::Holder &v2)
//{
//    return Core::Qt::SortFilterModel::compareByFileNames(v1.as<QueryResultPathItem>()->info(), v2.as<QueryResultPathItem>()->info());
//}


QueryResultRootPathValueItem::QueryResultRootPathValueItem(const Interface::Adaptor<IStorage> &container, const EntityValue &value, Item *parent) :
    QueryResultPathItem(container, toUnicode(value.value().asString()), parent),
    m_value(value),
    m_container(container)
{
//    lock(tr("Updating..."));
}

bool QueryResultRootPathValueItem::isRootPathValue()
{
    return true;
}

void QueryResultRootPathValueItem::open() const
{
    Interface::Holder apps = Module::desktop().applications(m_file->as<IEntry>()->type());

    if (apps.isValid())
    {
        ASSERT(apps->as<IApplications>() != NULL);
        IApplications::const_iterator iterator = apps->as<IApplications>()->begin();

        if (iterator != apps->as<IApplications>()->end())
        {
            ASSERT((*iterator)->as<IApplication>() != NULL);
            (*iterator)->as<IApplication>()->open(m_file->as<IEntry>());
        }
    }
}

//void QueryResultRootPathValueItem::update(SnapshotItem *item)
//{
//    m_items.clear();
//
//    if (item)
//    {
//        m_info = item->info().take();
//
//        if (m_info->isDir())
//        {
//            m_thisContainer = item->thisContainer().take();
//
//            for (SnapshotItem::const_iterator i = item->begin(), end = item->end(); i != end; ++i)
//                m_items.push_back(QueryResultItem::Holder(new QueryResultPathValueItem(m_thisContainer.data(), (*i), this)));
//        }
//
//        qSort(m_items.begin(), m_items.end(), compareByFileNames);
//    }
//    else
//        m_info = new InvalidInfo(toUnicode(m_value.value().asString()));
//}

}}
