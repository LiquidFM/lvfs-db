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

#ifndef LVFS_DB_QUERYCONSTRAINTSMODEL_H_
#define LVFS_DB_QUERYCONSTRAINTSMODEL_H_

#include <QtCore/QAbstractItemModel>
#include <liquiddb/EntityConstraint>
#include "../../../../constraints/lvfs_db_BaseConstraint.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE QueryConstraintsModel : public QAbstractItemModel
{
public:
    QueryConstraintsModel(QObject *parent = 0);

    /* QAbstractItemModel */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    void add(const QModelIndex &index);
    void add(const BaseConstraint::Holder &constraint, const QModelIndex &index);
    void remove(const QModelIndex &index);

    BaseConstraint::Holder constraint() { return m_root; }

private:
    QVariant data(BaseConstraint *item, int column, int role) const;

private:
    BaseConstraint::Holder m_root;
    QVariant m_andTypeLabel;
    QVariant m_orTypeLabel;
};

}}

#endif /* LVFS_DB_QUERYCONSTRAINTSMODEL_H_ */
