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

#include "lvfs_db_SelectValueDialog.h"
#include "../../model/items/lvfs_db_ValueItem.h"

#include <brolly/assert.h>


SelectValueDialog::SelectValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, QWidget *parent) :
    EntityValueDialog(storage, reader, parent)
{}

SelectValueDialog::~SelectValueDialog()
{}

EntityValue SelectValueDialog::value()
{
    QModelIndex index = currentIndex();
    ASSERT(index.isValid());

    Item *item = static_cast<Item *>(index.internalPointer());

    if (item->parent())
        do
            item = item->parent();
        while (item->parent());

    return static_cast<ValueItem *>(item)->value();
}

void SelectValueDialog::accept()
{
    if (currentIndex().isValid())
        EntityValueDialog::accept();
    else
        warning(tr("You must choose one of the values."));
}
