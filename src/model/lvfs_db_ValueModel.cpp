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

#include "lvfs_db_ValueModel.h"

#include "items/lvfs_db_FileItem.h"
#include "items/lvfs_db_ValueItem.h"
#include "items/lvfs_db_PropertyItem.h"

#include <lvfs/Module>
#include <lvfs/IEntry>
#include <lvfs/IDirectory>

#include <brolly/assert.h>


namespace LVFS {
namespace Db {

ValueModel::ValueModel(QObject *parent) :
    Model(parent)
{}

::Qt::ItemFlags ValueModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void ValueModel::add(const QModelIndex &property, const EntityValue &value)
{
    ASSERT(property.isValid());
    PropertyItem *item = static_cast<PropertyItem *>(property.internalPointer());

    beginInsertRows(property, item->size(), item->size());
    item->add(new ValueItem(value, item));
    endInsertRows();
}

void ValueModel::add(const QModelIndex &property, const EntityValue::List &values)
{
    ASSERT(property.isValid());
    PropertyItem *item = static_cast<PropertyItem *>(property.internalPointer());

    beginInsertRows(property, item->size(), item->size() + values.size() - 1);
    for (auto i : values)
        item->add(new ValueItem(i, item));
    endInsertRows();
}

void ValueModel::set(const Interface::Adaptor<IStorage> &storage, const EntityValue &value)
{
    ASSERT(m_items.empty());
    PropertyItem *item;

    for (auto i : value.entity().properties())
    {
        m_items.push_back(item = new PropertyItem(i.second));
        const EntityValue::Values &list = CompositeEntityValue(value).values(i.second.entity);

        for (auto i : list)
            if (storage->schema(i.second.entity()) == IStorage::Path)
                item->add(new FileItem(i.second, storage.interface()->as<IDirectory>()->entry(i.second.value().asString()), item));
            else
                item->add(new ValueItem(i.second, item));
    }
}

void ValueModel::set(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const Files &files)
{
    ASSERT(m_items.empty());
    PropertyItem *item;

    for (auto i : value.entity().properties())
    {
        m_items.push_back(item = new PropertyItem(i.second));
        const EntityValue::Values &list = CompositeEntityValue(value).values(i.second.entity);

        for (auto i : list)
            if (storage->schema(i.second.entity()) == IStorage::Path)
                item->add(new FileItem(i.second, files.find(i.first)->second, item));
            else
                item->add(new ValueItem(i.second, item));
    }
}

void ValueModel::remove(const QModelIndex &index)
{
    ASSERT(index.isValid());
    Item *item = static_cast<Item *>(index.internalPointer());

    beginRemoveRows(parent(index), index.row(), index.row());
    static_cast<PropertyItem *>(item->parent())->remove(index.row());
    endRemoveRows();
}

void ValueModel::update(const QModelIndex &index)
{
    emit dataChanged(index, index);
}

}}
