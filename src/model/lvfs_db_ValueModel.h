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

#ifndef LVFS_DB_VALUEMODEL_H_
#define LVFS_DB_VALUEMODEL_H_

#include <efc/Map>
#include <lvfs-db/IStorage>
#include <liquiddb/EntityValue>
#include "lvfs_db_Model.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE ValueModel : public Model
{
public:
    typedef EFC::Map<Entity::Id, Interface::Holder> Files;

public:
    ValueModel(QObject *parent = 0);

    virtual ::Qt::ItemFlags flags(const QModelIndex &index) const;

    void add(const QModelIndex &property, const EntityValue &value);
    void add(const QModelIndex &property, const EntityValue::List &values);
    void set(const Interface::Adaptor<IStorage> &storage, const EntityValue &value);
    void set(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const Files &files);

    void remove(const QModelIndex &index);
    void update(const QModelIndex &index);
};

}}

#endif /* LVFS_DB_VALUEMODEL_H_ */
