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

#ifndef LVFS_DB_STORAGE_H_
#define LVFS_DB_STORAGE_H_

#include <lvfs/IEntry>
#include <lvfs/IDirectory>
#include <lvfs-db/IStorage>
#include <lvfs-core/INodeFactory>
#include <lvfs-core/IViewFactory>


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE Storage : public ExtendsBy<IStorage, Core::INodeFactory, Core::IViewFactory>
{
public:
    Storage(const Interface::Holder &file, const Interface::Holder &storage);
    virtual ~Storage();

    /* IStorage */
    virtual bool isDbValid() const;
    virtual const char *lastError() const;
    virtual Interface::Holder file() const;
    virtual const LiquidDb::Storage::Entities &entities() const;

    virtual bool transaction();
    virtual bool commit();
    virtual void rollback();

    virtual EntityValueReader entityValues(const Entity &entity) const;
    virtual EntityValueReader entityValues(const Entity &entity, const Constraint &constraint) const;

    virtual Schemas schema(const Entity &entity) const;
    virtual bool setSchema(const Entity &entity, Schemas schema);

    virtual Rect editorGeometry(const Entity &entity) const;
    virtual bool setEditorGeometry(const Entity &entity, const Rect &geometry);

    virtual Rect listGeometry(const Entity &entity) const;
    virtual bool setListGeometry(const Entity &entity, const Rect &geometry);

    virtual Entity createEntity(Entity::Type type, const EFC::String &name, const EFC::String &title);
    virtual bool removeEntity(const Entity &entity);

    virtual bool addProperty(const Entity &entity, const Entity &property, const EFC::String &name);
    virtual bool renameProperty(const Entity &entity, const Entity &property, const EFC::String &name);
    virtual bool removeProperty(const Entity &entity, const Entity &property);

    virtual EntityValue addValue(const Entity &entity);
    virtual bool addValue(const EntityValue &entityValue, const EntityValue &propertyValue);
    virtual bool addValue(const EntityValue &entityValue, const EntityValue::List &propertyValues);
    virtual EntityValue addValue(const Entity &entity, const EFC::Variant &value);
    virtual bool updateValue(const EntityValue &value, const EFC::Variant &newValue);
    virtual bool removeValue(const Entity &entity, const Entity::IdsList &ids);
    virtual bool removeValue(const EntityValue &entityValue, const EntityValue &propertyValue);

    /* Core::INodeFactory */
    virtual Interface::Holder createNode(const Interface::Holder &file, const Interface::Holder &parent) const;

    /* Core::IViewFactory */
    virtual Interface::Holder createView() const;

private:
    Interface::Holder m_fileStorage;
    LiquidDb::Storage m_storage;
};

}}

#endif /* LVFS_DB_STORAGE_H_ */
