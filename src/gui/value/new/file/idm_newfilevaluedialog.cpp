/**
 * This file is part of QFM.
 *
 * Copyright (C) 2011-2014 Dmitriy Vilkov, <dav.daemon@gmail.com>
 *
 * QFM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QFM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QFM. If not, see <http://www.gnu.org/licenses/>.
 */
#include "idm_newfilevaluedialog.h"
#include "../../model/items/lvfs_db_CompositeValuePropertyItem.h"


//NewFileValueDialog::NewFileValueDialog(const Interface::Adaptor<IStorage> &container, const EntityValue &value, const CompositeValueModel::Files &files, QWidget *parent) :
//    NewCompositeValueDialog(container, value, files, parent)
//{}

void NewFileValueDialog::addValue()
{
    QModelIndex index = currentIndex();

//    if (index.isValid() && static_cast<CompositeValueItem *>(index.internalPointer())->isProperty() &&
//        static_cast<CompositeValuePropertyItem *>(index.internalPointer())->entity().type() != Entity::Path)
        doAddValue(index);
}

void NewFileValueDialog::removeValue()
{
    QModelIndex index = currentIndex();

//    if (index.isValid() && !static_cast<CompositeValueItem *>(index.internalPointer())->isProperty() &&
//        static_cast<CompositeValuePropertyItem *>(index.internalPointer())->entity()->type() != Database::Path)
        doRemoveValue(index);
}
