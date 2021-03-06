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

#include "lvfs_db_Model.h"


namespace LVFS {
namespace Db {

Model::ListItem::ListItem(Item *parent) :
    Item(parent)
{}

Model::ListItem::~ListItem()
{
    clear();
}

Model::Item *Model::ListItem::at(size_type index) const
{
    return m_items.at(index);
}

Model::Item::size_type Model::ListItem::size() const
{
    return m_items.size();
}

Model::ListItem::size_type Model::ListItem::indexOf(Item *item) const
{
    for (auto i = m_items.begin(); i != m_items.end(); ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

void Model::ListItem::clear()
{
    for (auto &i : m_items)
        delete i;

    m_items.clear();
}

Model::Model(QObject *parent)
{}

Model::~Model()
{
    for (auto &i : m_items)
        delete i;
}

Model::size_type Model::size() const
{
    return m_items.size();
}

Model::Item *Model::at(size_type index) const
{
    return m_items.at(index);
}

Model::size_type Model::indexOf(Item *item) const
{
    for (auto i = m_items.begin(); i != m_items.end(); ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

}}
