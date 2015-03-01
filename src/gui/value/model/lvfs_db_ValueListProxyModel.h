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

#ifndef LVFS_DB_VALUELISTPROXYMODEL_H_
#define LVFS_DB_VALUELISTPROXYMODEL_H_

#include <platform/utils.h>
#include <QtGui/QSortFilterProxyModel>


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE ValueListProxyModel : public QSortFilterProxyModel
{
    PLATFORM_MAKE_NONCOPYABLE(ValueListProxyModel)

public:
    ValueListProxyModel(QObject *parent = 0);

    void setFilter(const QString &filter);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    QString m_filter;
};

}}

#endif /* LVFS_DB_VALUELISTPROXYMODEL_H_ */
