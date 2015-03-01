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

#ifndef LVFS_DB_ENTITIESLISTMODELITEM_H_
#define LVFS_DB_ENTITIESLISTMODELITEM_H_

#include <liquiddb/Entity>
#include "../../../../model/lvfs_db_Model.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE EntitiesListItem : public Model::ListItem
{
public:
    EntitiesListItem(const Entity::Property &property, Model::Item *parent = 0);

    /* IdmItem */
    virtual QVariant data(qint32 column, qint32 role) const;

    const Entity &entity() const { return m_property.entity; }
    const Entity::Property &property() const { return m_property; }

    void setEntity(const Entity &value) { m_property.entity = value; }
    void setName(const ::EFC::String &name) { m_property.name = name; }

private:
    Entity::Property m_property;
};

}}

#endif /* LVFS_DB_ENTITIESLISTMODELITEM_H_ */
