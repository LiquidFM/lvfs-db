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

#include "lvfs_db_QueryResultCompositeRootItem.h"
#include "lvfs_db_QueryResultPathPropertyItem.h"
#include "lvfs_db_QueryResultPropertyItem.h"


namespace LVFS {
namespace Db {

QueryResultCompositeRootItem::QueryResultCompositeRootItem(EFC::List<Interface::Holder> &files, const Interface::Adaptor<IStorage> &container, const EntityValue &value, Item *parent) :
    QueryResultRootItem(value, parent),
    m_items(value.entity().properties().size())
{
    int pos = 0;
    QueryResultPropertyItem *item;

    for (auto i : value.entity().properties())
    {
//        if (container->schema(i.second.entity) == IStorage::Path)
//        {
//            item = new QueryResultPathPropertyItem(i.second, this);
//            item.as<QueryResultPathPropertyItem>()->add(files, container.container(), CompositeEntityValue(value).values(i.second.entity));
//        }
//        else
        {
            item = new QueryResultPropertyItem(i.second, this);
            item->add(CompositeEntityValue(value).values(i.second.entity));
        }

        m_items[pos++] = item;
    }
}

QueryResultCompositeRootItem::~QueryResultCompositeRootItem()
{
    for (auto i : m_items)
        delete i;
}

QueryResultCompositeRootItem::Item *QueryResultCompositeRootItem::at(size_type index) const
{
    return m_items.at(index);
}

QueryResultCompositeRootItem::size_type QueryResultCompositeRootItem::size() const
{
    return m_items.size();
}

QueryResultCompositeRootItem::size_type QueryResultCompositeRootItem::indexOf(Item *item) const
{
    for (auto i = m_items.begin(), end = m_items.end(); i != end; ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

}}
