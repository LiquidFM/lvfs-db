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

#ifndef LVFS_DB_ISTORAGE_H_
#define LVFS_DB_ISTORAGE_H_

#include <lvfs/Interface>
#include <liquiddb/Storage>
#include <liquiddb/EntityConstraint>
#include <liquiddb/EntityValueReader>


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PUBLIC IStorage
{
    DECLARE_INTERFACE(LVFS::Db::IStorage)

public:
    enum MenuId
    {
        Create,
        Find,
        List
    };

    enum MetaProperties
    {
        Schema,
        EditorGeometry,
        ListGeometry
    };

    enum Schemas
    {
        Default,
        Path,
        Rating
    };

    struct Rect
    {
        int x;
        int y;
        int width;
        int height;
    };

public:
    virtual ~IStorage();

    virtual bool isDbValid() const = 0;
    virtual const char *lastError() const = 0;
    virtual Interface::Holder file() const = 0;
    virtual const LiquidDb::Storage::Entities &entities() const = 0;

    virtual bool transaction() = 0;
    virtual bool commit() = 0;
    virtual void rollback() = 0;

    virtual EntityValueReader entityValues(const Entity &entity) const = 0;
    virtual EntityValueReader entityValues(const Entity &entity, const Constraint &constraint) const = 0;

    virtual Schemas schema(const Entity &entity) const = 0;
    virtual bool setSchema(const Entity &entity, Schemas schema) = 0;

    virtual Rect editorGeometry(const Entity &entity) const = 0;
    virtual bool setEditorGeometry(const Entity &entity, const Rect &geometry) = 0;

    virtual Rect listGeometry(const Entity &entity) const = 0;
    virtual bool setListGeometry(const Entity &entity, const Rect &geometry) = 0;

    virtual Entity createEntity(Entity::Type type, const ::EFC::String &name, const ::EFC::String &title) = 0;
    virtual bool removeEntity(const Entity &entity) = 0;

    virtual bool addProperty(const Entity &entity, const Entity &property, const ::EFC::String &name) = 0;
    virtual bool renameProperty(const Entity &entity, const Entity &property, const ::EFC::String &name) = 0;
    virtual bool removeProperty(const Entity &entity, const Entity &property) = 0;

    virtual EntityValue addValue(const Entity &entity) = 0;
    virtual bool addValue(const EntityValue &entityValue, const EntityValue &propertyValue) = 0;
    virtual bool addValue(const EntityValue &entityValue, const EntityValue::List &propertyValues) = 0;
    virtual EntityValue addValue(const Entity &entity, const ::EFC::Variant &value) = 0;
    virtual bool updateValue(const EntityValue &value, const ::EFC::Variant &newValue) = 0;
    virtual bool removeValue(const Entity &entity, const Entity::IdsList &ids) = 0;
    virtual bool removeValue(const EntityValue &entityValue, const EntityValue &propertyValue) = 0;
};

}}

#endif /* LVFS_DB_ISTORAGE_H_ */
