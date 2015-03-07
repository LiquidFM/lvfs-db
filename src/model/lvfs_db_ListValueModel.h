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

#ifndef LVFS_DB_VALUELISTMODEL_H_
#define LVFS_DB_VALUELISTMODEL_H_

#include <liquiddb/EntityValueReader>
#include "lvfs_db_ValueModel.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class PLATFORM_MAKE_PRIVATE ListValueModel : public ValueModel
{
public:
    ListValueModel(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, QObject *parent = 0);

    /* QAbstractItemModel */
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual void fetchMore(const QModelIndex &parent);
    virtual bool canFetchMore(const QModelIndex &parent = QModelIndex()) const;

    bool isValid() const { return m_reader.isValid(); }
    QString lastError() const { return QString(); }

    EntityValue take(const QModelIndex &index);

    void close() { m_reader.close(); }

protected:
    enum { PrefetchLimit = 64 };

protected:
    const Interface::Adaptor<IStorage> &m_storage;
    EntityValueReader m_reader;
};

}}

#endif /* LVFS_DB_VALUELISTMODEL_H_ */
