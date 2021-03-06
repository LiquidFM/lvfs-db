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

#include "lvfs_db_Storage.h"
#include "nodes/root/lvfs_db_RootNode.h"
#include "nodes/root/lvfs_db_RootView.h"


namespace LVFS {
namespace Db {

Storage::Storage(const Interface::Holder &file, const Interface::Holder &storage) :
    ExtendsBy(file),
    m_fileStorage(storage),
    m_storage(m_fileStorage->as<IEntry>()->location(), false)
{}

Storage::~Storage()
{}

bool Storage::isDbValid() const
{
    return m_storage.isValid();
}

const char *Storage::lastError() const
{
    return "";
}

Interface::Holder Storage::file() const
{
    return original();
}

const LiquidDb::Storage::Entities &Storage::entities() const
{
    return m_storage.entities();
}

bool Storage::transaction()
{
    return m_storage.transaction();
}

bool Storage::commit()
{
    return m_storage.commit();
}

void Storage::rollback()
{
    m_storage.rollback();
}

EntityValueReader Storage::entityValues(const Entity &entity) const
{
    return m_storage.entityValues(entity);
}

EntityValueReader Storage::entityValues(const Entity &entity, const Constraint &constraint) const
{
    return m_storage.entityValues(entity, constraint);
}

Storage::Schemas Storage::schema(const Entity &entity) const
{
    EFC::Variant value(m_storage.metaPropertyValue(entity, Schema));

    if (value.isValid())
        return static_cast<Schemas>(value.asInt8());

    return Default;
}

bool Storage::setSchema(const Entity &entity, Schemas schema)
{
    return m_storage.setMetaPropertyValue(entity, Schema, EFC::Variant(schema));
}

Storage::Rect Storage::editorGeometry(const Entity &entity) const
{
    ::EFC::Variant value(m_storage.metaPropertyValue(entity, EditorGeometry));

    if (value.isValid())
    {
        size_t size;
        const int32_t *data = reinterpret_cast<const int32_t *>(value.asBinary(size));
        ASSERT(size == sizeof(int32_t) * 4);
        return { data[0], data[1], data[2], data[3] };
    }

    return { 0, 0, 0, 0 };
}

bool Storage::setEditorGeometry(const Entity &entity, const Rect &geometry)
{
    unsigned char buffer[sizeof(int32_t) * 4];
    int32_t *data = reinterpret_cast<int32_t *>(buffer);

    data[0] = geometry.x;
    data[1] = geometry.y;
    data[2] = geometry.width;
    data[3] = geometry.height;

    return m_storage.setMetaPropertyValue(entity, EditorGeometry, ::EFC::Variant(buffer, sizeof(buffer)));
}

Storage::Rect Storage::listGeometry(const Entity &entity) const
{
    ::EFC::Variant value(m_storage.metaPropertyValue(entity, ListGeometry));

    if (value.isValid())
    {
        size_t size;
        const int32_t *data = reinterpret_cast<const int32_t *>(value.asBinary(size));
        ASSERT(size == sizeof(int32_t) * 4);
        return { data[0], data[1], data[2], data[3] };
    }

    return { 0, 0, 0, 0 };
}

bool Storage::setListGeometry(const Entity &entity, const Rect &geometry)
{
    unsigned char buffer[sizeof(int32_t) * 4];
    int32_t *data = reinterpret_cast<int32_t *>(buffer);

    data[0] = geometry.x;
    data[1] = geometry.y;
    data[2] = geometry.width;
    data[3] = geometry.height;

    return m_storage.setMetaPropertyValue(entity, ListGeometry, ::EFC::Variant(buffer, sizeof(buffer)));
}

Entity Storage::createEntity(Entity::Type type, const EFC::String &name, const EFC::String &title)
{
    return m_storage.createEntity(type, name, title);
}

bool Storage::removeEntity(const Entity &entity)
{
    return m_storage.removeEntity(entity);
}

bool Storage::addProperty(const Entity &entity, const Entity &property, const EFC::String &name)
{
    return m_storage.addProperty(entity, property, name);
}

bool Storage::renameProperty(const Entity &entity, const Entity &property, const EFC::String &name)
{
    return m_storage.renameProperty(entity, property, name);
}

bool Storage::removeProperty(const Entity &entity, const Entity &property)
{
    return m_storage.removeProperty(entity, property);
}

EntityValue Storage::addValue(const Entity &entity)
{
    return m_storage.addValue(entity);
}

bool Storage::addValue(const EntityValue &entityValue, const EntityValue &propertyValue)
{
    return m_storage.addValue(entityValue, propertyValue);
}

bool Storage::addValue(const EntityValue &entityValue, const EntityValue::List &propertyValues)
{
    return m_storage.addValue(entityValue, propertyValues);
}

EntityValue Storage::addValue(const Entity &entity, const EFC::Variant &value)
{
    return m_storage.addValue(entity, value);
}

bool Storage::updateValue(const EntityValue &value, const EFC::Variant &newValue)
{
    return m_storage.updateValue(value, newValue);
}

bool Storage::removeValue(const Entity &entity, const Entity::IdsList &ids)
{
    return m_storage.removeValue(entity, ids);
}

bool Storage::removeValue(const EntityValue &entityValue, const EntityValue &propertyValue)
{
    return m_storage.removeValue(entityValue, propertyValue);
}

Interface::Holder Storage::createNode(const Interface::Holder &file, const Interface::Holder &parent) const
{
    return Interface::Holder(new (std::nothrow) RootNode(file, parent));
}

Interface::Holder Storage::createView() const
{
    return Interface::Holder(new (std::nothrow) RootView());
}

}}
