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

#ifndef LVFS_DB_NEWFILEVALUEDIALOG_H_
#define LVFS_DB_NEWFILEVALUEDIALOG_H_

#include <QtCore/QStringList>

#include "../composite/lvfs_db_NewCompositeValueDialog.h"


class PLATFORM_MAKE_PRIVATE NewFileValueDialog : public NewCompositeValueDialog
{
    Q_OBJECT

public:
    NewFileValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, QWidget *parent = 0);

protected:
    virtual void addValue();
    virtual void removeValue();
};

#endif /* LVFS_DB_NEWFILEVALUEDIALOG_H_ */
