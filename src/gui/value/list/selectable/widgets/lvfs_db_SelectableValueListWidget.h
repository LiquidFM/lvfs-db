/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2014 Dmitriy Vilkov, <dav.daemon@gmail.com>
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

#ifndef LVFS_DB_SELECTABLEVALUELISTWIDGET_H_
#define LVFS_DB_SELECTABLEVALUELISTWIDGET_H_

#include "../../editable/widgets/lvfs_db_EditableValueListWidget.h"


class SelectableValueListWidget : public EditableValueListWidget
{
public:
    SelectableValueListWidget(const Interface::Adaptor<IStorage> &container, const EntityValueReader &reader, NestedDialog *parent);

    virtual void accept();
};

#endif /* LVFS_DB_SELECTABLEVALUELISTWIDGET_H_ */
