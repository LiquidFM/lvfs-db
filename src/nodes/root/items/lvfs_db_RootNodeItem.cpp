/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2012 Dmitriy Vilkov, <dav.daemon@gmail.com>
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

#include "lvfs_db_RootNodeItem.h"


namespace LVFS {
namespace Db {

RootNodeItem::RootNodeItem(Base *parent) :
    Core::Tools::TreeModel::Item(parent)
{}

bool RootNodeItem::isRoot()
{
    return false;
}

bool RootNodeItem::isFiles()
{
    return false;
}

bool RootNodeItem::isEntity()
{
    return false;
}

bool RootNodeItem::isProperty()
{
    return false;
}

RootNodeListItem::RootNodeListItem(Base *parent) :
    RootNodeItem(parent)
{}

RootNodeListItem::~RootNodeListItem()
{
    for (auto i : m_items)
        delete i;
}

RootNodeListItem::Base *RootNodeListItem::at(size_type index) const
{
    return m_items.at(index);
}

RootNodeListItem::size_type RootNodeListItem::size() const
{
    return m_items.size();
}

RootNodeListItem::size_type RootNodeListItem::indexOf(Base *item) const
{
    for (auto i = m_items.begin(), end = m_items.end(); i != end; ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

}}
