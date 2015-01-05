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

#ifndef LVFS_DB_QUERYRESULTPATHPROPERTYITEM_H_
#define LVFS_DB_QUERYRESULTPATHPROPERTYITEM_H_

#include <lvfs-db/IStorage>
#include "lvfs_db_QueryResultPropertyItem.h"


namespace LVFS {
namespace Db {

class QueryResultPathPropertyItem : public QueryResultPropertyItem
{
public:
    QueryResultPathPropertyItem(const Entity::Property &property, Item *parent);

    virtual bool isPathProperty();

//    void add(const IFileContainer *container, const EntityValue &value);
//    void add(const IFileContainer *container, const EntityValue::List &values);
    void add(EFC::List<Interface::Holder> &files, const Interface::Adaptor<IStorage> &container, const EntityValue::Values &values);
};

}}

#endif /* LVFS_DB_QUERYRESULTPATHPROPERTYITEM_H_ */
