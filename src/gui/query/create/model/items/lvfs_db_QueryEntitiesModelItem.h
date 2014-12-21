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

#ifndef LVFS_DB_QUERYENTITIESMODELITEM_H_
#define LVFS_DB_QUERYENTITIESMODELITEM_H_

#include <efc/Vector>
#include <liquiddb/Entity>
#include "../../../../../model/lvfs_db_Model.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class QueryEntitiesModelItem : public Model::Item
{
public:
    QueryEntitiesModelItem(const Entity::Property &property, Model::Item *parent = 0);
    virtual ~QueryEntitiesModelItem();

    /* Base */
    virtual Model::Item *at(size_type index) const;
    virtual size_type size() const;
    virtual size_type indexOf(Model::Item *item) const;
    virtual QVariant data(qint32 column, qint32 role) const;

    const Entity &entity() const { return m_property.entity; }
    const Entity::Property &property() const { return m_property; }

protected:
    friend class QueryEntitiesModel;
    void add(Model::Item *item) { m_items.push_back(item); }
    void remove(size_type index) { m_items.erase(m_items.begin() + index); }

private:
    Entity::Property m_property;
    EFC::Vector<Model::Item *> m_items;
};

}}

#endif /* LVFS_DB_QUERYENTITIESMODELITEM_H_ */
