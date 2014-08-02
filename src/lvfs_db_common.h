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

#ifndef LVFS_DB_COMMON_H_
#define LVFS_DB_COMMON_H_

#include <efc/Map>
#include <efc/String>
#include <efc/Variant>
#include <QtCore/QRect>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QVariant>
#include <QtCore/QDateTime>
#include <QtCore/QCoreApplication>
#include <liquiddb/Storage>
#include <lvfs-db/IStorage>


namespace LVFS {
namespace Db {

using namespace LiquidDb;


QByteArray fromUnicode(const QString &string);
QString toUnicode(const ::EFC::String &string);
QVariant toQVariant(const ::EFC::Variant &value);
QRect toQRect(const IStorage::Rect &rect);
IStorage::Rect fromQRect(const QRect &rect);

/* Meta-function "EntityValueType" */
template <Entity::Type EntityType> struct EntityValueType {};
template <> struct EntityValueType<Entity::Int>      { typedef int       type; };
template <> struct EntityValueType<Entity::String>   { typedef QString   type; };
template <> struct EntityValueType<Entity::Date>     { typedef QDate     type; };
template <> struct EntityValueType<Entity::Time>     { typedef QTime     type; };
template <> struct EntityValueType<Entity::DateTime> { typedef QDateTime type; };
template <> struct EntityValueType<Entity::Memo>     { typedef QString   type; };

/* Meta-function "EntityValueType" */
inline ::EFC::Variant toVariant(int value) { return ::EFC::Variant(static_cast<uint32_t>(value)); }
inline ::EFC::Variant toVariant(const QString &value) { return fromUnicode(value).data(); }
inline ::EFC::Variant toVariant(const QDate &value) { return ::EFC::Variant(QDateTime(value, QTime()).toTime_t()); }
inline ::EFC::Variant toVariant(const QTime &value) { return ::EFC::Variant(QDateTime(QDate::currentDate(), value).toTime_t()); }
inline ::EFC::Variant toVariant(const QDateTime &value) { return ::EFC::Variant(value.toTime_t()); }

struct EntityTypeDescription
{
    QString label;
    QString description;
};

class EntityTypes : public EFC::Map<Entity::Type, EntityTypeDescription>
{
    Q_DECLARE_TR_FUNCTIONS(EntityTypes)

public:
    EntityTypes();

    static const EntityTypes &instance();
};

}}

#endif /* LVFS_DB_COMMON_H_ */
