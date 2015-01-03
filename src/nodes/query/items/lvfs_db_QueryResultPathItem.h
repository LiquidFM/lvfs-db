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

#ifndef LVFS_DB_QUERYRESULTPATHITEM_H_
#define LVFS_DB_QUERYRESULTPATHITEM_H_

#include <efc/Vector>
#include "lvfs_db_QueryResultItem.h"


namespace LVFS {
namespace Db {

class QueryResultPathItem : public QueryResultItem
{
public:
    typedef EFC::Vector<QueryResultItem *> Container;

public:
//    QueryResultPathItem(IFileInfo::Holder &info, Item *parent);
//    QueryResultPathItem(const IFileContainer *container, const QString &fileName, Item *parent);
    virtual ~QueryResultPathItem();

    /* Core::Tools::TreeModel::Item */
    virtual Item *at(size_type index) const;
    virtual size_type size() const;
    virtual size_type indexOf(Item *item) const;

    virtual QVariant data(qint32 column, qint32 role) const;

    /* QueryResultItem */
    virtual bool isRoot();
    virtual bool isProperty();
    virtual bool isValue();
    virtual bool isPath();

//    const IFileInfo::Holder &info() const { return m_info; }
//    IFileInfo::Holder &info() { return m_info; }
//    const Location location() const { return m_location; }

    virtual void open() const = 0;

//    Node *node() const { return m_node; }
//    void setNode(Node *node) { m_node = node; }

protected:
//    IFileInfo::Holder m_info;
//    Location m_location;
//    Node *m_node;
    Container m_items;
};

}}

#endif /* LVFS_DB_QUERYRESULTPATHITEM_H_ */
