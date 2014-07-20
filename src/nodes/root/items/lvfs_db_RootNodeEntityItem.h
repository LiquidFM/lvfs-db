/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2012 Dmitriy Vilkov, <dav.daemon@gmail.com>
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

#ifndef LVFS_DB_ROOTNODEENTITYITEM_H_
#define LVFS_DB_ROOTNODEENTITYITEM_H_

#include <liquiddb/Entity>
#include "lvfs_db_RootNodeItem.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class RootNodeEntityItem : public RootNodeListItem
{
public:
    RootNodeEntityItem(const Entity &entity, Base *parent = 0);

    /* Base */
    virtual QVariant data(qint32 column, qint32 role) const;

    /* RootNodeItem */
    virtual bool isEntity();

    const Entity &entity() const { return m_entity; }

protected:
    friend class RootNode;
    void add(RootNodeItem *item) { m_items.push_back(item); }
    void remove(size_type index) { delete m_items[index]; m_items.erase(m_items.begin() + index); }

private:
    Entity m_entity;
    QString m_entityName;
};

}}

#endif /* LVFS_DB_ROOTNODEENTITYITEM_H_ */
