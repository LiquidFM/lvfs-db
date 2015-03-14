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

ValueModel::ValueModel(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, QObject *parent) :
    Model(parent),
    m_storage(storage),
    m_reader()
{
    PropertyItem *item;

    for (auto i : value.entity().properties())
    {
        m_items.push_back(item = new PropertyItem(i.second));
        const EntityValue::Values &list = CompositeEntityValue(value).values(i.second.entity);

        for (auto i : list)
            if (m_storage->schema(i.second.entity()) == IStorage::Path)
                item->add(new FileItem(i.second, storage.interface()->as<IDirectory>()->entry(i.second.value().asString()), item));
            else
                item->add(new ValueItem(i.second, item));
    }
}

ValueModel::ValueModel(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, QObject *parent) :
    Model(parent),
    m_storage(storage),
    m_reader(reader)
{}

ValueModel::ValueModel(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, QObject *parent) :
    Model(parent),
    m_storage(storage),
    m_reader()
{
    PropertyItem *item;

    for (auto i : value.entity().properties())
    {
        m_items.push_back(item = new PropertyItem(i.second));
        const EntityValue::Values &list = CompositeEntityValue(value).values(i.second.entity);

        for (auto i : list)
            if (m_storage->schema(i.second.entity()) == IStorage::Path)
                item->add(new FileItem(i.second, files.find(i.first)->second, item));
            else
                item->add(new ValueItem(i.second, item));
    }
}

::Qt::ItemFlags ValueModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void ValueModel::fetchMore(const QModelIndex &parent)
{
    Container items;
    EntityValue value;

    items.reserve(PrefetchLimit);

    if (m_reader.entity().type() == Entity::Composite)
        for (qint32 actualLimit = 0; actualLimit < PrefetchLimit; ++actualLimit)
            if ((value = m_reader.next()).isValid())
                items.push_back(new ValueItem(m_storage, value));
            else
                break;
    else
        for (qint32 actualLimit = 0; actualLimit < PrefetchLimit; ++actualLimit)
            if ((value = m_reader.next()).isValid())
                items.push_back(new ValueItem(value));
            else
                break;

    if (!items.empty())
    {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size() + items.size() - 1);
        std::move(items.begin(), items.end(), std::back_inserter(m_items));
        endInsertRows();
    }
}

bool ValueModel::canFetchMore(const QModelIndex &parent) const
{
    return m_reader.isValid() && !parent.isValid() && !m_reader.eof();
}

EntityValue ValueModel::take(const QModelIndex &index)
{
    EntityValue res;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    res = static_cast<ValueItem *>(m_items.at(index.row()))->take();
    delete m_items.at(index.row());
    m_items.erase(m_items.begin() + index.row());
    endRemoveRows();

    return res;
}

QModelIndex ValueModel::add(const EntityValue &value)
{
    ASSERT(value.isValid());

    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.push_back(new ValueItem(value));
    endInsertRows();

    return index(m_items.size() - 1, 0, QModelIndex());
}

QModelIndex ValueModel::add(PropertyItem *parent, const EntityValue &value)
{
    ASSERT(parent != NULL);
    ASSERT(value.isValid());
    QModelIndex parentIdx = index(parent);

    beginInsertRows(parentIdx, parent->size(), parent->size());
    if (m_storage->schema(value.entity()) == IStorage::Path)
        parent->add(new FileItem(value, m_storage.interface()->as<IDirectory>()->entry(value.value().asString()), parent));
    else
        parent->add(new ValueItem(value, parent));
    endInsertRows();

    return index(parent->size() - 1, 0, parentIdx);
}

void ValueModel::remove(const QModelIndex &index)
{
    ASSERT(index.isValid());
    Db::Item *item = static_cast<Db::Item *>(index.internalPointer());

    if (item->parent())
    {
        beginRemoveRows(parent(index), index.row(), index.row());
        item->parent()->remove(index.row());
        endRemoveRows();
    }
    else
    {
        beginRemoveRows(QModelIndex(), index.row(), index.row());
        delete m_items[index.row()];
        m_items.erase(m_items.begin() + index.row());
        endRemoveRows();
    }
}

void ValueModel::update(const QModelIndex &index)
{
    emit dataChanged(index, index);
}

}}
