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

#include "lvfs_db_CompositeValueValueItem.h"


namespace LVFS {
namespace Db {

CompositeValueValueItem::CompositeValueValueItem(const EntityValue &value, Model::Item *parent) :
    CompositeValueItem(parent),
    m_value(value)
{}

QVariant CompositeValueValueItem::data(qint32 column, qint32 role) const
{
    if (role == Qt::DisplayRole)
        return toQVariant(m_value.value());
    else
        return QVariant();
}

bool CompositeValueValueItem::isValue() const
{
    return true;
}

}}
