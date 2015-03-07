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

#ifndef LVFS_DB_VALUEITEM_H_
#define LVFS_DB_VALUEITEM_H_

#include <lvfs-db/IStorage>
#include "lvfs_db_Item.h"


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE ValueItem : public Item
{
public:
    ValueItem(const EntityValue &value, Item *parent = 0);
    ValueItem(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, Item *parent = 0);
    virtual ~ValueItem();

    virtual QVariant data(qint32 column, qint32 role) const;

    virtual bool isValue() const;

    const EntityValue &value() const { return m_value; }
    EntityValue take() { EntityValue res(m_value); m_value = EntityValue(); return res; }

protected:
    EntityValue m_value;
    QVariant m_cache;
};

}}

#endif /* LVFS_DB_VALUEITEM_H_ */

