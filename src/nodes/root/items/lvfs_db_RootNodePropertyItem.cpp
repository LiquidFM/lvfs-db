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

#include "lvfs_db_RootNodePropertyItem.h"
#include "../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

RootNodePropertyItem::RootNodePropertyItem(const Entity::Property &property, Item *parent) :
    RootNodeEntityItem(property.entity, parent),
    m_property(property),
    m_label(QString(toUnicode(m_property.name)).append(QString::fromLatin1(" (")).append(toUnicode(m_property.entity.name())).append(QChar(L')')))
{}

RootNodePropertyItem::RootNodePropertyItem(const Entity &property, const ::EFC::String &name, Item *parent) :
    RootNodeEntityItem(property, parent),
    m_property(property, name),
    m_label(QString(toUnicode(m_property.name)).append(QString::fromLatin1(" (")).append(toUnicode(m_property.entity.name())).append(QChar(L')')))
{}

QVariant RootNodePropertyItem::data(qint32 column, qint32 role) const
{
    if (role == Qt::DisplayRole)
        return m_label;
    else
        return QVariant();
}

bool RootNodePropertyItem::isProperty()
{
    return true;
}

QString RootNodePropertyItem::name() const
{
    return toUnicode(m_property.name);
}

}}
