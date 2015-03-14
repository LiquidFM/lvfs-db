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

#include "lvfs_db_EntityValueDialog.h"
#include "../../model/items/lvfs_db_FileItem.h"


EntityValueDialog::EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(storage, value, &m_handler, this)
{
    QRect geometry = toQRect(storage->editorGeometry(value.entity()));

    if (geometry.isValid())
        setGeometry(geometry);

    m_handler.registerMouseDoubleClickEventHandler(&EntityValueDialog::openFile1);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Insert, &EntityValueDialog::addValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Delete, &EntityValueDialog::removeValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Return, &EntityValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Enter,  &EntityValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_F2,     &EntityValueDialog::edit);
    m_mainWidget.setViewToolTip(tr("INS - add value\nDEL - remove value\nF2 - edit selected item\nENTER or double click on file to open it"));

    setCentralWidget(&m_mainWidget);
}

EntityValueDialog::EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(storage, value, files, &m_handler, this)
{
    QRect geometry = toQRect(storage->editorGeometry(value.entity()));

    if (geometry.isValid())
        setGeometry(geometry);

    m_handler.registerMouseDoubleClickEventHandler(&EntityValueDialog::openFile1);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Insert, &EntityValueDialog::addValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Delete, &EntityValueDialog::removeValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Return, &EntityValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Enter,  &EntityValueDialog::openFile2);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_F2,     &EntityValueDialog::edit);
    m_mainWidget.setViewToolTip(tr("INS - add value\nDEL - remove value\nF2 - edit selected item\nENTER or double click on file to open it"));

    setCentralWidget(&m_mainWidget);
}

void EntityValueDialog::addValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && static_cast<Item *>(index.internalPointer())->isProperty())
        doAddValue();
}

void EntityValueDialog::removeValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && !static_cast<Item *>(index.internalPointer())->isProperty())
        doRemoveValue();
}

void EntityValueDialog::openFile1()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && static_cast<Item *>(index.internalPointer())->isPath())
        static_cast<FileItem *>(index.internalPointer())->open();
}

void EntityValueDialog::openFile2()
{
    QModelIndex index = currentIndex();

    if (index.isValid() && static_cast<Item *>(index.internalPointer())->isPath())
        static_cast<FileItem *>(index.internalPointer())->open();
    else
        accept();
}

void EntityValueDialog::edit()
{
    QModelIndex index = currentIndex();

    if (index.isValid())
        doEdit();
}
