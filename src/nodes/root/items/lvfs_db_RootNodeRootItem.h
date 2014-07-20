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

#ifndef LVFS_DB_ROOTNODEROOTITEM_H_
#define LVFS_DB_ROOTNODEROOTITEM_H_

#include "lvfs_db_RootNodeItem.h"


namespace LVFS {
namespace Db {

class RootNodeRootItem : public RootNodeItem
{
public:
    RootNodeRootItem();

    /* Base */
    virtual QVariant data(qint32 column, qint32 role) const;

    /* RootNodeItem */
    virtual bool isRoot();

private:
    QVariant m_label;
};

}}

#endif /* LVFS_DB_ROOTNODEROOTITEM_H_ */
