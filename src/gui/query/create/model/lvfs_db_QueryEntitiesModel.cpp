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

#include "lvfs_db_QueryEntitiesModel.h"
#include "items/lvfs_db_QueryEntitiesModelItem.h"


namespace LVFS {
namespace Db {

QueryEntitiesModel::QueryEntitiesModel(QObject *parent) :
    Model(parent)
{}

void QueryEntitiesModel::add(const Entity::Property &property)
{
    QueryEntitiesModelItem *item;

    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.push_back(item = new QueryEntitiesModelItem(property));
    expand(item);
    endInsertRows();
}

void QueryEntitiesModel::remove(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    delete m_items[index.row()];
    m_items.erase(m_items.begin() + index.row());
    endRemoveRows();
}

void QueryEntitiesModel::expand(Item *p)
{
    QueryEntitiesModelItem *item;
    QueryEntitiesModelItem *parent = static_cast<QueryEntitiesModelItem *>(p);

    for (auto i : parent->entity().properties())
    {
        parent->add(item = new QueryEntitiesModelItem(i.second, parent));
        expand(item);
    }
}

}}
