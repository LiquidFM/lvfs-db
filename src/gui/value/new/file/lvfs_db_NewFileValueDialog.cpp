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

#include "lvfs_db_NewFileValueDialog.h"
#include "../../../../model/items/lvfs_db_PropertyItem.h"


NewFileValueDialog::NewFileValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, QWidget *parent) :
    NewCompositeValueDialog(storage, value, files, parent)
{}

void NewFileValueDialog::addValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && static_cast<Item *>(index.internalPointer())->isProperty() &&
        storage()->schema(static_cast<PropertyItem *>(index.internalPointer())->entity()) != IStorage::Path)
        doAddValue();
}

void NewFileValueDialog::removeValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && !static_cast<Item *>(index.internalPointer())->isProperty() &&
        storage()->schema(static_cast<PropertyItem *>(index.internalPointer())->entity()) != IStorage::Path)
        doRemoveValue();
}
