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

#ifndef LVFS_DB_ROOTNODEITEM_H_
#define LVFS_DB_ROOTNODEITEM_H_

#include <efc/Vector>
#include <lvfs-core/tools/models/TreeModel>


namespace LVFS {
namespace Db {

class RootNodeItem : public Core::Tools::TreeModel::Item
{
public:
    RootNodeItem(Item *parent);

    virtual bool isFiles();
    virtual bool isEntity();
    virtual bool isProperty();
};


class RootNodeListItem : public RootNodeItem
{
public:
    typedef EFC::Vector<RootNodeItem *> Container;

public:
    RootNodeListItem(Item *parent);
    virtual ~RootNodeListItem();

    /* Base */
    virtual Item *at(size_type index) const;
    virtual size_type size() const;
    virtual size_type indexOf(Item *item) const;

protected:
    Container m_items;
};

}}

#endif /* LVFS_DB_ROOTNODEITEM_H_ */
