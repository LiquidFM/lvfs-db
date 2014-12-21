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

#ifndef LVFS_DB_MODEL_H_
#define LVFS_DB_MODEL_H_

#include <efc/Vector>
#include <lvfs-core/tools/models/TreeModel>


namespace LVFS {
namespace Db {

class Model : public Core::Tools::TreeModel
{
public:
    class ListItem : public Item
    {
    public:
        typedef EFC::Vector<Item *> Container;

    public:
        ListItem(Item *parent);
        virtual ~ListItem();

        /* Base */
        virtual Item *at(size_type index) const;
        virtual size_type size() const;
        virtual size_type indexOf(Item *item) const;

    protected:
        Container m_items;
    };

public:
    Model(QObject *parent = 0);
    virtual ~Model();

protected:
    virtual size_type size() const;
    virtual Item *at(size_type index) const;
    virtual size_type indexOf(Item *item) const;

protected:
    EFC::Vector<Item *> m_items;
};

}}

#endif /* LVFS_DB_MODEL_H_ */
