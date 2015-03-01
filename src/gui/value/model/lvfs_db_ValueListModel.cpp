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

#include "lvfs_db_ValueListModel.h"
#include "../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

ValueListModel::ValueListModel(const EntityValueReader &reader, QObject *parent) :
    QAbstractItemModel(parent),
    m_reader(reader)
{}

int ValueListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return m_items.size();
}

int ValueListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant ValueListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return toQVariant(m_items.at(index.row()).value());
    else
        return QVariant();
}

Qt::ItemFlags ValueListModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ValueListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void ValueListModel::fetchMore(const QModelIndex &parent)
{
    List list;
    EntityValue item;

    list.reserve(PrefetchLimit);

    for (qint32 actualLimit = 0; actualLimit < PrefetchLimit; ++actualLimit)
        if ((item = m_reader.next()).isValid())
            list.push_back(item);
        else
            break;

    if (!list.isEmpty())
        add(list);
}

bool ValueListModel::canFetchMore(const QModelIndex &parent) const
{
    return !parent.isValid() && !m_reader.eof();
}

QModelIndex ValueListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (hasIndex(row, column, parent))
        return createIndex(row, column);
    else
        return QModelIndex();
}

QModelIndex ValueListModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

EntityValue ValueListModel::take(const QModelIndex &index)
{
    EntityValue res;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    res = m_items.takeAt(index.row());
    endRemoveRows();

    return res;
}

void ValueListModel::add(const List &list)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size() + list.size() - 1);
    m_items.append(list);
    endInsertRows();
}

QModelIndex ValueListModel::add(const EntityValue &value)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.push_back(value);
    endInsertRows();

    return createIndex(m_items.size() - 1, 0);
}

void ValueListModel::remove(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_items.removeAt(index.row());
    endRemoveRows();
}

}}
