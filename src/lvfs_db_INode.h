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

#ifndef LVFS_DB_INODE_H_
#define LVFS_DB_INODE_H_

#include <QtCore/QAbstractItemModel>
#include <lvfs/Interface>


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE INode
{
    DECLARE_INTERFACE(LVFS::Db::INode)

public:
    virtual ~INode();

    virtual QAbstractItemModel *model() const = 0;

    virtual QModelIndex parentIndex() const = 0;
    virtual void setParentIndex(const QModelIndex &index) = 0;
};

}}

#endif /* LVFS_DB_INODE_H_ */
