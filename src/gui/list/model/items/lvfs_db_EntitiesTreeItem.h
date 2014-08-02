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

#ifndef LVFS_DB_MENUENTITIESTREEITEM_H_
#define LVFS_DB_MENUENTITIESTREEITEM_H_

#include <liquiddb/Entity>
#include "../../../../model/lvfs_db_Model.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class EntitiesTreeItem : public Model::ListItem
{
public:
    EntitiesTreeItem(const Entity &entity, Model::Item *parent = 0);

    /* IdmItem */
    virtual QVariant data(qint32 column, qint32 role) const;

    const Entity &entity() const { return m_entity; }

protected:
    friend class EntitiesTreeModel;
    void add(Model::ListItem *item) { m_items.push_back(item); }
    void remove(size_type index) { m_items.erase(m_items.begin() + index); }

private:
    const Entity &m_entity;
};

}}

#endif /* LVFS_DB_MENUENTITIESTREEITEM_H_ */
