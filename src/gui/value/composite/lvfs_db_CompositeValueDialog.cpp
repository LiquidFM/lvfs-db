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

#include "lvfs_db_CompositeValueDialog.h"
#include "../model/items/lvfs_db_CompositeValueValueItem.h"
#include "../model/items/lvfs_db_CompositeValuePropertyItem.h"
#include "../../../lvfs_db_common.h"


CompositeValueDialog::CompositeValueDialog(const Interface::Adaptor<IStorage> &container, const EntityValue &value, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(&m_handler, container, value, this)
{
    QRect geometry = toQRect(container->editorGeometry(value.entity()));

    if (geometry.isValid())
        setGeometry(geometry);

    m_handler.registerMouseDoubleClickEventHandler(&CompositeValueDialog::openFile1);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Insert, &CompositeValueDialog::addValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Delete, &CompositeValueDialog::removeValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Return, &CompositeValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Enter,  &CompositeValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_F2,     &CompositeValueDialog::edit);
    m_mainWidget.setViewToolTip(tr("INS - add value\nDEL - remove value\nF2 - edit selected item\nENTER or double click on file to open it"));

    setCentralWidget(&m_mainWidget);
}

CompositeValueDialog::CompositeValueDialog(const Interface::Adaptor<IStorage> &container, const EntityValue &value, const CompositeValueModel::Files &files, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(&m_handler, container, value, files, this)
{
    QRect geometry = toQRect(container->editorGeometry(value.entity()));

    if (geometry.isValid())
        setGeometry(geometry);

    m_handler.registerMouseDoubleClickEventHandler(&CompositeValueDialog::openFile1);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Insert, &CompositeValueDialog::addValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Delete, &CompositeValueDialog::removeValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Return, &CompositeValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Enter,  &CompositeValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_F2,     &CompositeValueDialog::edit);
    m_mainWidget.setViewToolTip(tr("INS - add value\nDEL - remove value\nF2 - edit selected item\nENTER or double click on file to open it"));

    setCentralWidget(&m_mainWidget);
}

void CompositeValueDialog::addValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && static_cast<CompositeValueItem *>(index.internalPointer())->isProperty())
        doAddValue(index);
}

void CompositeValueDialog::removeValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && !static_cast<CompositeValueItem *>(index.internalPointer())->isProperty())
        doRemoveValue(index);
}

void CompositeValueDialog::openFile1()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && static_cast<CompositeValueItem *>(index.internalPointer())->isPath())
        doOpenFile(index);
}

void CompositeValueDialog::openFile2()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && static_cast<CompositeValueItem *>(index.internalPointer())->isPath())
        doOpenFile(index);
    else
        accept();
}

void CompositeValueDialog::edit()
{
    QModelIndex index = currentIndex();

    if (index.isValid())
        doEdit(index);
}
