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

#ifndef LVFS_DB_COMPOSITEVALUEPATHITEM_H_
#define LVFS_DB_COMPOSITEVALUEPATHITEM_H_

#include "lvfs_db_CompositeValueItem.h"


namespace LVFS {
namespace Db {
using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE CompositeValuePathItem : public CompositeValueItem
{
public:
    CompositeValuePathItem(const EntityValue &value, Model::Item *parent = 0);

    /* CompositeValueItem */
    virtual bool isPath() const;

    virtual QString fileName() const = 0;
    virtual bool isFile() const = 0;
    virtual void open() const = 0;

    const EntityValue &value() const { return m_value; }
    EntityValue take() { EntityValue res(m_value); m_value = EntityValue(); return res; }

protected:
    EntityValue m_value;
};

}}

#endif /* LVFS_DB_COMPOSITEVALUEPATHITEM_H_ */
