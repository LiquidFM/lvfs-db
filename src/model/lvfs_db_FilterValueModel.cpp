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

#include "lvfs_db_FilterValueModel.h"
#include "items/lvfs_db_ValueItem.h"

#include <brolly/assert.h>
#include <cstring>


namespace LVFS {
namespace Db {

FilterValueModel::FilterValueModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{}

void FilterValueModel::setFilter(const QString &filter)
{
    m_filter = fromUnicode(filter);
    invalidateFilter();
}

bool FilterValueModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_filter.isEmpty() || sourceParent.isValid())
        return true;
    else
    {
        QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
        ASSERT(static_cast<Item *>(index.internalPointer())->isValue());
        return ::strstr(static_cast<ValueItem *>(index.internalPointer())->value().value().asString(), m_filter.data()) != NULL;
    }
}

bool FilterValueModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (static_cast<Item *>(left.internalPointer())->isValue() && static_cast<Item *>(right.internalPointer())->isValue())
        return ::strcmp(static_cast<ValueItem *>(left.internalPointer())->value().value().asString(), static_cast<ValueItem *>(right.internalPointer())->value().value().asString()) < 0;
    else
        return false;
}

}}
