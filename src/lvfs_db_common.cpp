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

#include "lvfs_db_common.h"

#include <lvfs-core/models/Qt/Node>


namespace LVFS {
namespace Db {

QByteArray fromUnicode(const QString &string)
{
    return Core::Qt::Node::fromUnicode(string);
}

QString toUnicode(const ::EFC::String &string)
{
    return Core::Qt::Node::toUnicode(string.c_str());
}

QVariant toQVariant(const ::EFC::Variant &value)
{
    switch (value.type())
    {
        case ::EFC::Variant::UINT8:
        case ::EFC::Variant::INT8:
        case ::EFC::Variant::UINT16:
        case ::EFC::Variant::INT16:
        case ::EFC::Variant::UINT32:
        case ::EFC::Variant::INT32:
        case ::EFC::Variant::UINT64:
        case ::EFC::Variant::INT64:
        case ::EFC::Variant::BOOL:
        case ::EFC::Variant::CHAR:
            return static_cast<qulonglong>(value.asUint64());

        case ::EFC::Variant::FLOAT:
            return value.asFloat();

        case ::EFC::Variant::DOUBLE:
            return value.asDouble();

        case ::EFC::Variant::STRING:
        case ::EFC::Variant::BINARY:
            return toUnicode(value.asString());
    }

    return QVariant();
}

QRect toQRect(const IStorage::Rect &rect)
{
    return QRect(rect.x, rect.y, rect.width, rect.height);
}

IStorage::Rect fromQRect(const QRect &rect)
{
    return { rect.x(), rect.y(), rect.width(), rect.height() };
}

EntityTypes::EntityTypes()
{
    EntityTypeDescription desc;

    desc = { tr("Int"),       tr("Integer type") };
    (*this)[Entity::Int]       = std::move(desc);

    desc = { tr("String"),    tr("String type (max length is 256 characters)") };
    (*this)[Entity::String]    = std::move(desc);

    desc = { tr("Date"),      tr("Date type") };
    (*this)[Entity::Date]      = std::move(desc);

    desc = { tr("Time"),      tr("Time type") };
    (*this)[Entity::Time]      = std::move(desc);

    desc = { tr("DateTime"),  tr("DateTime type") };
    (*this)[Entity::DateTime]  = std::move(desc);

    desc = { tr("Memo"),      tr("Memo type") };
    (*this)[Entity::Memo]      = std::move(desc);

    desc = { tr("Composite"), tr("Entity of this type consists of other entities") };
    (*this)[Entity::Composite] = std::move(desc);
}

const EntityTypes &EntityTypes::instance()
{
    static const EntityTypes entityTypes;
    return entityTypes;
}

}}
