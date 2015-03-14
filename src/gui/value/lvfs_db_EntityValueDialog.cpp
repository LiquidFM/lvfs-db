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
#include "../../lvfs_db_common.h"


EntityValueDialog::EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(storage, value, &m_handler, this)
{
    init(toQRect(storage->editorGeometry(m_mainWidget.entity())));
    setWindowTitle(tr("Editing value of \"%1\"").arg(toUnicode(m_mainWidget.entity().name())));
}

EntityValueDialog::EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(storage, reader, &m_handler, this)
{
    init(toQRect(storage->listGeometry(m_mainWidget.entity())));
    setWindowTitle(tr("Values of \"%1\"").arg(toUnicode(m_mainWidget.entity().name())));
}

EntityValueDialog::EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(storage, value, files, &m_handler, this)
{
    init(toQRect(storage->editorGeometry(m_mainWidget.entity())));
    setWindowTitle(tr("Editing value of \"%1\"").arg(toUnicode(m_mainWidget.entity().name())));
}

void EntityValueDialog::edit()
{
    m_mainWidget.edit();
}

bool EntityValueDialog::dblClick()
{
    return m_mainWidget.dblClick();
}

void EntityValueDialog::addValue()
{
    m_mainWidget.addValue();
}

void EntityValueDialog::removeValue()
{
    m_mainWidget.removeValue();
}

void EntityValueDialog::setFocusToFilter()
{
    m_mainWidget.setFocusToFilter();
}

void EntityValueDialog::init(const QRect &geometry)
{
    if (geometry.isValid())
        setGeometry(geometry);

    m_handler.registerMouseDoubleClickEventHandler(&EntityValueDialog::dblClick);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_F2,     &EntityValueDialog::edit);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Insert, &EntityValueDialog::addValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Delete, &EntityValueDialog::removeValue);
    m_handler.registerShortcut(Qt::CTRL,       Qt::Key_F,      &EntityValueDialog::setFocusToFilter);
    m_handler.registerShortcut(Qt::CTRL,       Qt::Key_Return, &EntityValueDialog::accept);

    setCentralWidget(&m_mainWidget);
}
