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

#include "lvfs_db_ValueItem.h"
#include "lvfs_db_FileItem.h"
#include "lvfs_db_PropertyItem.h"

#include <lvfs/IDirectory>


namespace LVFS {
namespace Db {

ValueItem::ValueItem(const EntityValue &value, Item *parent) :
    Item(parent),
    m_value(value),
    m_cache(toQVariant(m_value.value()))
{}

ValueItem::ValueItem(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, Item *parent) :
    Item(parent),
    m_value(value),
    m_cache(toQVariant(m_value.value()))
{
    init(storage);
}

ValueItem::~ValueItem()
{}

QVariant ValueItem::data(qint32 column, qint32 role) const
{
    if (role == Qt::DisplayRole)
        return m_cache;
    else
        return QVariant();
}

bool ValueItem::isValue() const
{
    return true;
}

void ValueItem::reset(const Interface::Adaptor<IStorage> &storage, const EntityValue &value)
{
    clear();

    m_value = value;
    m_cache = toQVariant(m_value.value());

    init(storage);
}

void ValueItem::init(const Interface::Adaptor<IStorage> &storage)
{
    PropertyItem *item;

    for (auto i : m_value.entity().properties())
    {
        m_items.push_back(item = new PropertyItem(i.second, this));
        const EntityValue::Values &list = CompositeEntityValue(m_value).values(i.second.entity);

        for (auto i : list)
            if (storage->schema(i.second.entity()) == IStorage::Path)
                item->add(new FileItem(i.second, storage.interface()->as<IDirectory>()->entry(i.second.value().asString()), item));
            else
                item->add(new ValueItem(i.second, item));
    }
}

}}
