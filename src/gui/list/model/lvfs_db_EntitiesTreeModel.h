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

#ifndef LVFS_DB_ENTITIESTREEMODEL_H_
#define LVFS_DB_ENTITIESTREEMODEL_H_

#include <liquiddb/Entity>
#include "../../../model/lvfs_db_Model.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE EntitiesTreeModel : public Model
{
public:
    EntitiesTreeModel(QObject *parent = 0);

    void add(const Entity &entity);
    void remove(const QModelIndex &index);

private:
    void doAdd(const Entity &entity);
    void doAdd(Item *item, const Entity &property);
    void doRemove(Item *item, size_type index);
    void expand(Item *parent);

private:
    typedef QMap<Entity, EFC::Vector<Item *>> Map;
    Map m_entities;
};

}}

#endif /* LVFS_DB_ENTITIESTREEMODEL_H_ */
