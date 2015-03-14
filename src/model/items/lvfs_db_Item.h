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

#ifndef LVFS_DB_ITEM_H_
#define LVFS_DB_ITEM_H_

#include <liquiddb/EntityValue>
#include "../lvfs_db_Model.h"
#include "../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE Item : public Model::ListItem
{
public:
    Item(Item *parent = 0);
    virtual ~Item();

    Item *parent() const { return static_cast<Item *>(ListItem::parent()); }
    void remove(size_type index) { Container::iterator i = m_items.begin() + index; delete (*i); m_items.erase(i); }

    virtual bool isPath() const;
    virtual bool isValue() const;
    virtual bool isProperty() const;
};

}}

#endif /* LVFS_DB_ITEM_H_ */
