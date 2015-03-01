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

#include "lvfs_db_EntitiesTreeModel.h"
#include "items/lvfs_db_EntitiesTreeItem.h"


namespace LVFS {
namespace Db {

EntitiesTreeModel::EntitiesTreeModel(QObject *parent) :
    Model(parent)
{}

void EntitiesTreeModel::add(const Entity &entity)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    doAdd(entity);
    endInsertRows();
}

void EntitiesTreeModel::remove(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    delete m_items[index.row()];
    m_items.erase(m_items.begin() + index.row());
    endRemoveRows();
}

void EntitiesTreeModel::doAdd(const Entity &entity)
{
    EntitiesTreeItem *item;

    m_items.push_back(item = new EntitiesTreeItem(entity));
    m_entities[entity].push_back(item);
    expand(item);
}

void EntitiesTreeModel::doAdd(Item *item, const Entity &property)
{
    EntitiesTreeItem *child;

    static_cast<EntitiesTreeItem *>(item)->add(child = new EntitiesTreeItem(property, item));
    m_entities[property].push_back(child);
    expand(child);
}

void EntitiesTreeModel::doRemove(Item *item, size_type index)
{
    EFC::Vector<Item *> &items = m_entities[static_cast<EntitiesTreeItem *>(item)->entity()];

    for (EFC::Vector<Item *>::iterator i = items.begin(); i != items.end(); ++i)
        if (*i == item)
        {
            items.erase(i);
            break;
        }

    static_cast<EntitiesTreeItem *>(item->parent())->remove(index);
}

void EntitiesTreeModel::expand(Item *p)
{
    EntitiesTreeItem *item;
    EntitiesTreeItem *parent = static_cast<EntitiesTreeItem *>(p);

    for (auto i : parent->entity().properties())
    {
        parent->add(item = new EntitiesTreeItem(i.second.entity, parent));
        m_entities[i.second.entity].push_back(item);
        expand(item);
    }
}

}}
