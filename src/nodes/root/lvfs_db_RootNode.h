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

#ifndef LVFS_DB_ROOTNODE_H_
#define LVFS_DB_ROOTNODE_H_

#include <efc/Map>
#include <efc/Vector>
#include <QtGui/QIcon>
#include <liquiddb/Entity>
#include <lvfs-db/IStorage>
#include <lvfs-core/INode>
#include <lvfs-core/models/Node>
#include <lvfs-core/tools/models/TreeModel>
#include "items/lvfs_db_RootNodeItem.h"
#include "../../lvfs_db_INode.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE RootNode : public Core::Tools::TreeModel, public Complements<Core::Node, Db::INode>
{
public:
    RootNode(const Interface::Holder &container, const Interface::Holder &parent);
    virtual ~RootNode();

public: /* Core::INode */
    virtual void refresh(int depth = 0);
    virtual void opened(const Interface::Holder &view);
    virtual void closed(const Interface::Holder &view);
    virtual void accept(const Interface::Holder &view, Files &files);
    virtual void copy(const Interface::Holder &view, const Interface::Holder &dest, Files &files, bool move = false);
    virtual void remove(const Interface::Holder &view, Files &files);

    virtual void clear();

    virtual Interface::Holder node(const Interface::Holder &file) const;
    virtual void setNode(const Interface::Holder &file, const Interface::Holder &node);

public: /* Core::Tools::TreeModel */
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

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

private:
    void doAdd(const Entity &entity);
    void doRemove(const Entity &entity);
    void doAdd(const QModelIndex &index, Item *item, const Entity &property, const EFC::String &propertyName);
    void doRemove(const QModelIndex &index, Item *item, Item *property);
    void expand(Item *parent);

private:
    typedef EFC::Map<Entity, EFC::Vector<Item *>> EntitiesMap;

private:
    EntitiesMap m_entities;
    EFC::Vector<Item *> m_items;
    Interface::Adaptor<IStorage> m_container;
    EFC::Set<Interface::Holder> m_views;
    QModelIndex m_currentIndex;

private:
    Geometry m_geometry;
    Sorting m_sorting;
};

}}

#endif /* LVFS_DB_ROOTNODE_H_ */
