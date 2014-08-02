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
#include "idm_newcompositevaluedialog.h"
#include "../../../../lvfs_db_common.h"


NewCompositeValueDialog::NewCompositeValueDialog(const Interface::Adaptor<IStorage> &container, const EntityValue &value, QWidget *parent) :
    CompositeValueDialog(container, value, parent)
{
    setWindowTitle(tr("New value for \"%1\"").arg(toUnicode(value.entity().name())));
}

//NewCompositeValueDialog::NewCompositeValueDialog(const Interface::Adaptor<IStorage> &container, const EntityValue &value, const CompositeValueModel::Files &files, QWidget *parent) :
//    CompositeValueDialog(container, value, files, parent)
//{
//    setWindowTitle(tr("New value for \"%1\"").arg(toUnicode(value.entity().name())));
//}
