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

#ifndef LVFS_DB_COMPOSITEVALUEPROPERTYITEM_H_
#define LVFS_DB_COMPOSITEVALUEPROPERTYITEM_H_

#include "lvfs_db_CompositeValueItem.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class CompositeValuePropertyItem : public CompositeValueItem
{
public:
    typedef QList<Model::Item *> Container;

public:
    CompositeValuePropertyItem(const Entity::Property &property, Model::Item *parent = 0);
    virtual ~CompositeValuePropertyItem();

    /* Base */
    virtual Model::Item *at(size_type index) const;
    virtual size_type size() const;
    virtual size_type indexOf(Model::Item *item) const;

    virtual QVariant data(qint32 column, qint32 role) const;

    /* CompositeValueItem */
    virtual bool isProperty() const;

    const Entity &entity() const { return m_property.entity; }
    QString name() const { return toUnicode(m_property.name); }
    void setName(const QString &value) { m_property.name = fromUnicode(value).data(); }

protected:
    friend class CompositeValueModel;
    void add(Model::Item *item) { m_items.push_back(item); }
    void remove(size_type index) { delete m_items.takeAt(index); }

private:
    Entity::Property m_property;
    Container m_items;
};

}}

#endif /* LVFS_DB_COMPOSITEVALUEPROPERTYITEM_H_ */
