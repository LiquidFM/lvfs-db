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

#include "lvfs_db_Storage.h"
#include "nodes/root/lvfs_db_RootNode.h"
#include "nodes/root/lvfs_db_RootView.h"


namespace LVFS {
namespace Db {

Storage::Storage(const Interface::Holder &file, const Interface::Holder &storage) :
    m_file(file),
    m_fileStorage(storage),
    m_storage(m_fileStorage->as<IEntry>()->location(), false),
    m_error(),
    m_lastError(&m_error)
{}

Storage::~Storage()
{}

const char *Storage::title() const
{
    return m_file->as<IEntry>()->title();
}

const char *Storage::schema() const
{
    return m_file->as<IEntry>()->schema();
}

const char *Storage::location() const
{
    return m_file->as<IEntry>()->location();
}

const IType *Storage::type() const
{
    return m_file->as<IEntry>()->type();
}

Storage::const_iterator Storage::begin() const
{
    return m_file->as<IDirectory>()->begin();
}

Storage::const_iterator Storage::end() const
{
    return m_file->as<IDirectory>()->end();
}

Interface::Holder Storage::entry(const char *name) const
{
    return m_file->as<IDirectory>()->entry(name);
}

bool Storage::rename(const Interface::Holder &file, const char *name)
{
    return m_file->as<IDirectory>()->rename(file, name);
}

bool Storage::remove(const Interface::Holder &file)
{
    return m_file->as<IDirectory>()->remove(file);
}

time_t Storage::cTime() const
{
    return m_file->as<IFsFile>()->cTime();
}

time_t Storage::mTime() const
{
    return m_file->as<IFsFile>()->mTime();
}

time_t Storage::aTime() const
{
    return m_file->as<IFsFile>()->aTime();
}

int Storage::permissions() const
{
    return m_file->as<IFsFile>()->permissions();
}

bool Storage::setPermissions(int value)
{
    return m_file->as<IFsFile>()->setPermissions(value);
}

bool Storage::isDbValid() const
{
    return m_storage.isValid();
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

const Error &Storage::lastError() const
{
    return *m_lastError;
}

}}
