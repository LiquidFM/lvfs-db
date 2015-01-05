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

#ifndef LVFS_DB_QUERYRESULTSNODE_H_
#define LVFS_DB_QUERYRESULTSNODE_H_

#include <efc/Vector>
#include <lvfs-db/IStorage>
#include <lvfs-core/INode>
#include <lvfs-core/models/Node>
#include <lvfs-core/tools/models/TreeModel>
#include <liquiddb/EntityValueReader>
//#include "items/lvfs_db_RootNodeItem.h"
#include "../../lvfs_db_INode.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE QueryResultsNode : public Core::Tools::TreeModel, public Complements<Core::Node, Db::INode>
{
public:
    QueryResultsNode(const Interface::Adaptor<IStorage> &container, const EntityValueReader &reader, const Interface::Holder &parent);
    virtual ~QueryResultsNode();

public: /* Core::Tools::TreeModel */
    virtual void fetchMore(const QModelIndex &parent);
    virtual bool canFetchMore(const QModelIndex &parent = QModelIndex()) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

public: /* Core::INode */
    virtual void refresh(int depth = 0);
    virtual void opened(const Interface::Holder &view);
    virtual void closed(const Interface::Holder &view);

    virtual void clear();

public: /* Db::INode */
    virtual QAbstractItemModel *model() const;

    virtual const Geometry &geometry() const;
    virtual const Sorting &sorting() const;

    virtual QModelIndex currentIndex() const;
    virtual void setCurrentIndex(const QModelIndex &index);

    virtual Interface::Holder search(const QModelIndex &file, const Interface::Holder &view);
    virtual Interface::Holder activated(const QModelIndex &file, const Interface::Holder &view);

protected: /* Core::Tools::TreeModel */
    virtual size_type size() const;
    virtual Item *at(size_type index) const;
    virtual size_type indexOf(Item *item) const;

protected: /* Core::INode */
    virtual Interface::Holder node(const Interface::Holder &file) const;
    virtual void setNode(const Interface::Holder &file, const Interface::Holder &node);

private:
    enum { PrefetchLimit = 64 };

private:
    Interface::Adaptor<IStorage> m_container;
    EntityValueReader m_reader;
    EFC::Vector<Item *> m_items;

private:
    Geometry m_geometry;
    Sorting m_sorting;
    QModelIndex m_currentIndex;
};

}}

#endif /* LVFS_DB_QUERYRESULTSNODE_H_ */
