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

#ifndef LVFS_DB_VALUEDELEGATE_H_
#define LVFS_DB_VALUEDELEGATE_H_

#include <lvfs-db/IStorage>
#include "lvfs_db_Delegate.h"


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE ValueDelegate : public Delegate
{
    PLATFORM_MAKE_NONCOPYABLE(ValueDelegate)

public:
    ValueDelegate(const Interface::Adaptor<IStorage> &storage, const Entity &entity, QObject *parent = 0);

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    const Interface::Adaptor<IStorage> &m_storage;
    const Entity &m_entity;
};

}}

#endif /* LVFS_DB_VALUEDELEGATE_H_ */
