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

#include "lvfs_db_RootNodeEntityItem.h"
#include "../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

RootNodeEntityItem::RootNodeEntityItem(const Entity &entity, Item *parent) :
    RootNodeListItem(parent),
    m_entity(entity),
    m_entityName(toUnicode(m_entity.name()))
{}

QVariant RootNodeEntityItem::data(qint32 column, qint32 role) const
{
    if (role == Qt::DisplayRole)
        return m_entityName;
    else
        return QVariant();
}

bool RootNodeEntityItem::isEntity()
{
    return true;
}

}}
