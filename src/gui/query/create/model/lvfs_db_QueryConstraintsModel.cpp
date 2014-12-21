/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2012 Dmitriy Vilkov, <dav.daemon@gmail.com>
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

#include "lvfs_db_QueryConstraintsModel.h"
#include "items/lvfs_db_QueryConstraintsRootItem.h"
#include "../../../../constraints/value/lvfs_db_ValueConstraint.h"
#include "../../../../lvfs_db_common.h"


namespace LVFS {
namespace Db {

QueryConstraintsModel::QueryConstraintsModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_root(new QueryConstraintsRootItem()),
    m_andTypeLabel(tr("(...AND...)")),
    m_orTypeLabel(tr("(...OR...)"))
{}

int QueryConstraintsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        if (static_cast<BaseConstraint *>(parent.internalPointer())->isGroup())
            return static_cast<GroupConstraint *>(parent.internalPointer())->size();
        else
            return 0;
    else
        return 1;
}

int QueryConstraintsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant QueryConstraintsModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
        return data(static_cast<BaseConstraint *>(index.internalPointer()), index.column(), role);
    else
        return data(const_cast<QueryConstraintsRootItem *>(m_root.as<QueryConstraintsRootItem>()), index.column(), role);
}

Qt::ItemFlags QueryConstraintsModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant QueryConstraintsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
        switch (section)
        {
            case 0:
                return tr("Constraint");

            case 1:
            {
                switch (role)
                {
                    case Qt::DisplayRole:
                        return tr("Type");

                    case Qt::TextAlignmentRole:
                        return Qt::AlignCenter;
                }

                break;
            }
        }

    return QVariant();
}

QModelIndex QueryConstraintsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (hasIndex(row, column, parent))
        if (parent.isValid())
            if (static_cast<BaseConstraint *>(parent.internalPointer())->isGroup())
                return createIndex(row, column, static_cast<GroupConstraint *>(parent.internalPointer())->at(row).as<void>());
            else
                return createIndex(row, column, m_root.as<QueryConstraintsRootItem>()->at(row).as<void>());
        else
            return createIndex(row, column, const_cast<QueryConstraintsRootItem *>(m_root.as<QueryConstraintsRootItem>()));
    else
        return QModelIndex();
}

QModelIndex QueryConstraintsModel::parent(const QModelIndex &child) const
{
    if (child.isValid())
        if (BaseConstraint *parent = static_cast<BaseConstraint *>(child.internalPointer())->parent())
            if (parent->parent())
                return createIndex(static_cast<GroupConstraint *>(parent->parent())->indexOf(parent), 0, parent);
            else
                return createIndex(0, 0, const_cast<QueryConstraintsRootItem *>(m_root.as<QueryConstraintsRootItem>()));

    return QModelIndex();
}

void QueryConstraintsModel::add(const QModelIndex &index)
{
    if (!index.isValid())
    {
        beginInsertRows(QModelIndex(), m_root.as<QueryConstraintsRootItem>()->size(), m_root.as<QueryConstraintsRootItem>()->size());
        m_root.as<QueryConstraintsRootItem>()->add(BaseConstraint::Holder(new GroupConstraint(LiquidDb::GroupConstraint::And, m_root.as<QueryConstraintsRootItem>())));
        endInsertRows();
    }
    else
        if (static_cast<BaseConstraint *>(index.internalPointer())->isGroup())
        {
            beginInsertRows(index, static_cast<GroupConstraint *>(index.internalPointer())->size(), static_cast<GroupConstraint *>(index.internalPointer())->size());
            static_cast<GroupConstraint *>(index.internalPointer())->add(BaseConstraint::Holder(new GroupConstraint(LiquidDb::GroupConstraint::And, static_cast<GroupConstraint *>(index.internalPointer()))));
            endInsertRows();
        }
}

void QueryConstraintsModel::add(const BaseConstraint::Holder &constraint, const QModelIndex &index)
{
    if (index.isValid() && constraint.isValid())
    {
        beginInsertRows(index, static_cast<GroupConstraint *>(index.internalPointer())->size(), static_cast<GroupConstraint *>(index.internalPointer())->size());
        static_cast<GroupConstraint *>(index.internalPointer())->add(constraint);
        endInsertRows();
    }
}

void QueryConstraintsModel::remove(const QModelIndex &index)
{
    QModelIndex parentIndex = parent(index);
    GroupConstraint *parent = m_root.as<QueryConstraintsRootItem>();

    if (parentIndex.isValid())
        parent = static_cast<GroupConstraint *>(parentIndex.internalPointer());
    else
        if (static_cast<BaseConstraint *>(index.internalPointer()) == m_root.as<QueryConstraintsRootItem>())
            return;

    beginRemoveRows(parentIndex, index.row(), index.row());
    parent->remove(index.row());
    endRemoveRows();
}

QVariant QueryConstraintsModel::data(BaseConstraint *item, int column, int role) const
{
    switch (column)
    {
        case 0:
        {
            if (role == Qt::DisplayRole)
                if (item->isGroup())
                    switch (static_cast<GroupConstraint *>(item)->type())
                    {
                        case LiquidDb::GroupConstraint::And:
                            return m_andTypeLabel;

                        case LiquidDb::GroupConstraint::Or:
                            return m_orTypeLabel;
                    }
                else
                    return QString::fromLatin1("%1 %2 \"%3\"").
                            arg(toUnicode(static_cast<ValueConstraint *>(item)->property().name)).
                            arg(toUnicode(Constraint::operatorToString(static_cast<ValueConstraint*>(item)->op()))).
                            arg(toUnicode(static_cast<ValueConstraint *>(item)->value().value().asString()));

            break;
        }

        case 1:
        {
            if (item->isGroup())
                switch (role)
                {
                    case Qt::DisplayRole:
                        return toUnicode(LiquidDb::GroupConstraint::operatorToString(static_cast<GroupConstraint *>(item)->type()));

                    case Qt::TextAlignmentRole:
                        return Qt::AlignCenter;
                }

            break;
        }

        default:
            break;
    }

    return QVariant();
}

}}
