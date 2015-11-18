/**
 * This file is part of lvfs-core.
 *
 * Copyright (C) 2011-2015 Dmitriy Vilkov, <dav.daemon@gmail.com>
 *
 * lvfs-core is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lvfs-core is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lvfs-core. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LVFS_DB_SUBFILEITEM_H_
#define LVFS_DB_SUBFILEITEM_H_

#include <QtGui/QIcon>
#include <QtCore/QCoreApplication>
#include "lvfs_db_ValueItem.h"


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE SubFileItem : public Item
{
    Q_DECLARE_TR_FUNCTIONS(SubFileItem)

public:
    SubFileItem(const Interface::Holder &file, Item *parent = 0);
    SubFileItem(const EntityValue &value, const Interface::Holder &file, Item *parent = 0);
    virtual ~SubFileItem();

    const Interface::Holder &file() const { return m_file; }

    virtual QVariant data(qint32 column, qint32 role) const;

    virtual bool isPath() const;

    virtual void open() const;

private:
    void init();
    void init(const EntityValue &value);

private:
    Interface::Holder m_file;
    QString m_name;
    QString m_toolTip;
    QIcon m_icon;
};

}}

#endif /* LVFS_DB_SUBFILEITEM_H_ */
