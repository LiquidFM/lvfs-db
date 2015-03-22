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

class PropertyItem;
using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE ValueModel : public Model
{
public:
    typedef EFC::Map<Entity::Id, Interface::Holder> Files;

public:
    ValueModel(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, QObject *parent = 0);
    ValueModel(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, QObject *parent = 0);
    ValueModel(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, QObject *parent = 0);

    virtual ::Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual void fetchMore(const QModelIndex &parent);
    virtual bool canFetchMore(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex pathPropertyIndex(const QModelIndex &index) const;

    using Model::indexOf;
    EntityValue take(const QModelIndex &index);

    QModelIndex add(const EntityValue &value);
    QModelIndex add(PropertyItem *parent, const EntityValue &value);
    void remove(const QModelIndex &index);
    void update(const QModelIndex &index);

protected:
    enum { PrefetchLimit = 64 };

protected:
    const Interface::Adaptor<IStorage> &m_storage;
    EntityValueReader m_reader;
};

}}

#endif /* LVFS_DB_VALUEMODEL_H_ */
