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

#ifndef LVFS_DB_ROOTNODEFILESITEM_H_
#define LVFS_DB_ROOTNODEFILESITEM_H_

#include <lvfs/Interface>
#include <QtCore/QCoreApplication>
#include "lvfs_db_RootNodeItem.h"


namespace LVFS {
namespace Db {

class RootNodeFilesItem : public RootNodeItem
{
    Q_DECLARE_TR_FUNCTIONS(RootNodeFilesItem)

public:
    RootNodeFilesItem();

    /* Base */
    virtual QVariant data(qint32 column, qint32 role) const;

    /* IRootNodeItem */
    virtual bool isFiles();

    const Interface::Holder &node() const { return m_node; }
    void setNode(const Interface::Holder &node) { m_node = node; }

private:
    QVariant m_label;
    Interface::Holder m_node;
};

}}

#endif /* LVFS_DB_ROOTNODEFILESITEM_H_ */
