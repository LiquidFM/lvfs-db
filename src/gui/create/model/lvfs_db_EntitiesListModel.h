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

#ifndef LVFS_DB_ENTITIESLISTMODEL_H_
#define LVFS_DB_ENTITIESLISTMODEL_H_

#include <liquiddb/Entity>
#include "../../../model/lvfs_db_Model.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE EntitiesListModel : public Model
{
public:
    EntitiesListModel(QObject *parent = 0);

    /* Model */
    virtual int columnCount(const QModelIndex &parent) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    const Entity &entityAt(size_type index) const;
    const ::EFC::String &nameAt(size_type index) const;
    size_type size() const { return m_items.size(); }

    void add(const Entity &entity, const ::EFC::String &name);
    void remove(const QModelIndex &index);
};

}}

#endif /* LVFS_DB_ENTITIESLISTMODEL_H_ */
