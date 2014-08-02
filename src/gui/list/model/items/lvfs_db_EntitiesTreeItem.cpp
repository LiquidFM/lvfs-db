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

#include "lvfs_db_EntitiesTreeItem.h"
#include "../../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

EntitiesTreeItem::EntitiesTreeItem(const Entity &entity, Model::Item *parent) :
    Model::ListItem(parent),
    m_entity(entity)
{}

QVariant EntitiesTreeItem::data(qint32 column, qint32 role) const
{
    if (column == 0 && role == Qt::DisplayRole)
        return toUnicode(m_entity.name());
    else
        return QVariant();
}

}}
