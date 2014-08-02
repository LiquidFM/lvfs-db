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

#ifndef LVFS_DB_COMPOSITEVALUEMODEL_H_
#define LVFS_DB_COMPOSITEVALUEMODEL_H_

#include <QtCore/QMap>
#include <lvfs-db/IStorage>
#include <liquiddb/EntityValue>
#include "../../../model/lvfs_db_Model.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class CompositeValueModel : public Model
{
public:
    typedef EntityValue::List                      ValueList;
//    typedef QMap<Entity::Id, const SnapshotItem *> Files;

public:
    CompositeValueModel(const EntityValue &value, const Interface::Adaptor<IStorage> &container, QObject *parent = 0);
//    CompositeValueModel(const EntityValue &value, const Interface::Adaptor<IStorage> &container, const Files &files, QObject *parent = 0);

    virtual ::Qt::ItemFlags flags(const QModelIndex &index) const;

    Item *at(size_type index) const { return m_items.at(index); }
    size_type size() const { return m_items.size(); }

    void add(const QModelIndex &index, const EntityValue &value);
    void add(const QModelIndex &index, const ValueList &values);
    void remove(const QModelIndex &index);
    void update(const QModelIndex &index);
};

}}

#endif /* LVFS_DB_COMPOSITEVALUEMODEL_H_ */
