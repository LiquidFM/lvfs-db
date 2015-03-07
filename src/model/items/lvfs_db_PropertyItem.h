/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2015 Dmitriy Vilkov, <dav.daemon@gmail.com>
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

#ifndef LVFS_DB_PROPERTYITEM_H_
#define LVFS_DB_PROPERTYITEM_H_

#include "lvfs_db_Item.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE PropertyItem : public Item
{
public:
    PropertyItem(const Entity::Property &property, Item *parent = 0);
    virtual ~PropertyItem();

    virtual QVariant data(qint32 column, qint32 role) const;

    virtual bool isProperty() const;

    const Entity &entity() const { return m_property.entity; }

    const QString &name() const { return m_name; }
    void setName(const QString &value) { m_property.name = fromUnicode(m_name = value).data(); }

protected:
    friend class ValueModel;
    friend class ValueItem;
    void add(Item *item) { m_items.push_back(item); }
    void remove(size_type index) { Container::iterator i = m_items.begin() + index; delete (*i); m_items.erase(i); }

private:
    Entity::Property m_property;
    QString m_name;
};

}}

#endif /* LVFS_DB_PROPERTYITEM_H_ */
