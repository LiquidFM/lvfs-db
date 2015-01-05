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

#ifndef LVFS_DB_QUERYRESULTROOTITEM_H_
#define LVFS_DB_QUERYRESULTROOTITEM_H_

#include <liquiddb/EntityValue>
#include "lvfs_db_QueryResultItem.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class QueryResultRootItem : public QueryResultItem
{
public:
    QueryResultRootItem(const EntityValue &value, Item *parent = 0);

    /* Core::Tools::TreeModel::Item */
    virtual QVariant data(qint32 column, qint32 role) const;
    virtual bool isRoot();
    virtual bool isProperty();
    virtual bool isValue();
    virtual bool isPath();
    virtual bool isPathProperty();
    virtual bool isRootPathValue();

    const EntityValue &value() const { return m_value; }

private:
    EntityValue m_value;
};

}}

#endif /* LVFS_DB_QUERYRESULTROOTITEM_H_ */
