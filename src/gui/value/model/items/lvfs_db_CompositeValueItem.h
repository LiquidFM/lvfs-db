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

#ifndef IDM_COMPOSITEVALUEITEM_H_
#define IDM_COMPOSITEVALUEITEM_H_

#include <lvfs-db/IStorage>
#include <liquiddb/EntityValue>
#include "../../../../model/lvfs_db_Model.h"
#include "../../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

class CompositeValueItem : public Model::Item
{
public:
    CompositeValueItem(Item *parent = 0);

    virtual bool isPath() const;
    virtual bool isValue() const;
    virtual bool isProperty() const;
};

}}

#endif /* IDM_COMPOSITEVALUEITEM_H_ */
