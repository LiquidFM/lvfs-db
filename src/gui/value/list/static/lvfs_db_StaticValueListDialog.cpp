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

#include "lvfs_db_StaticValueListDialog.h"
#include "../../../../lvfs_db_common.h"


StaticValueListDialog::StaticValueListDialog(const Interface::Adaptor<IStorage> &container, const EntityValueReader &reader, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_widget(&m_handler, container, reader, this)
{
    QRect geometry = toQRect(container->listGeometry(m_widget.entity()));

    if (geometry.isValid())
        setGeometry(geometry);

    setWindowTitle(tr("Values of \"%1\"").arg(toUnicode(m_widget.entity().name())));

    m_handler.registerMouseDoubleClickEventHandler(&StaticValueListDialog::accept);
    m_handler.registerShortcut(Qt::CTRL, Qt::Key_F, &StaticValueListDialog::setFocusToFilter);
    m_widget.setViewToolTip(tr("CTRL+F - activate filter field"));

    setCentralWidget(&m_widget);
}

StaticValueListDialog::~StaticValueListDialog()
{
    m_widget.container()->setListGeometry(m_widget.entity(), fromQRect(geometry()));
}

EntityValue StaticValueListDialog::takeValue()
{
    return m_widget.takeValue();
}

void StaticValueListDialog::accept()
{
    if (currentIndex().isValid())
        QDialog::accept();
    else
        warning(windowTitle(), tr("You must select a value."));
}

QModelIndex StaticValueListDialog::currentIndex() const
{
    return m_widget.currentIndex();
}

void StaticValueListDialog::setFocusToFilter()
{
    m_widget.setFocusToFilter();
}
