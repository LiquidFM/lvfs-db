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

#include "lvfs_db_CompositeValueModel.h"
#include "items/lvfs_db_CompositeValueValueItem.h"
#include "items/lvfs_db_CompositeValuePropertyItem.h"
#include "items/lvfs_db_CompositeValuePathItem.h"
#include "items/lvfs_db_CompositeValueRealPathItem.h"
#include "items/lvfs_db_CompositeValuePossibleFileItem.h"
#include "items/lvfs_db_CompositeValuePossibleDirItem.h"


namespace LVFS {
namespace Db {

CompositeValueModel::CompositeValueModel(const EntityValue &value, const Interface::Adaptor<IStorage> &container, QObject *parent) :
    Model(parent)
{
    CompositeValuePropertyItem *item;

    for (auto i : value.entity().properties())
    {
        m_items.push_back(item = new CompositeValuePropertyItem(i.second));
        const EntityValue::Values &list = CompositeEntityValue(value).values(i.second.entity);

        for (auto i : list)
            if (container->schema(i.second.entity()) == IStorage::Path)
                item->add(new CompositeValueRealPathItem(i.second, item));
            else
                item->add(new CompositeValueValueItem(i.second, item));
    }
}

CompositeValueModel::CompositeValueModel(const EntityValue &value, const Interface::Adaptor<IStorage> &container, const Files &files, QObject *parent) :
    Model(parent)
{
//    const SnapshotItem *file;
//    CompositeValuePropertyItem *item;
//
//    for (auto i : value.entity().properties())
//    {
//        m_items.push_back(item = new CompositeValuePropertyItem(i.second));
//        const EntityValue::Values &list = CompositeEntityValue(value).values(i.second.entity);
//
//        for (auto i : list)
//            if (container->schema(i.second.entity()) == Interface::Adaptor<IStorage>::Path)
//            {
//                file = files.value(i.first);
//
//                if (file->info()->isFile())
//                    item->add(new CompositeValuePossibleFileItem(i.second, file, item));
//                else
//                    item->add(new CompositeValuePossibleDirItem(i.second, file, item));
//            }
//            else
//                item->add(new CompositeValueValueItem(i.second, item));
//    }
}

::Qt::ItemFlags CompositeValueModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void CompositeValueModel::add(const QModelIndex &index, const EntityValue &value)
{
    CompositeValuePropertyItem *item = static_cast<CompositeValuePropertyItem*>(index.internalPointer());

    beginInsertRows(index, item->size(), item->size());
    item->add(new CompositeValueValueItem(value, item));
    endInsertRows();
}

void CompositeValueModel::add(const QModelIndex &index, const ValueList &values)
{
    CompositeValuePropertyItem *item = static_cast<CompositeValuePropertyItem*>(index.internalPointer());

    beginInsertRows(index, item->size(), item->size() + values.size() - 1);

    for (auto i : values)
        item->add(new CompositeValueValueItem(i, item));

    endInsertRows();
}

void CompositeValueModel::remove(const QModelIndex &index)
{
    CompositeValueValueItem *item = static_cast<CompositeValueValueItem*>(index.internalPointer());

    beginRemoveRows(parent(index), index.row(), index.row());
    static_cast<CompositeValuePropertyItem*>(item->parent())->remove(index.row());
    endRemoveRows();
}

void CompositeValueModel::update(const QModelIndex &index)
{
    emit dataChanged(index, index);
}

}}
