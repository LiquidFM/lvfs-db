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

#include "lvfs_db_EntitiesListDelegate.h"
#include "items/lvfs_db_EntitiesListItem.h"
#include "../../../lvfs_db_common.h"

#include <efc/ScopedPointer>

#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>


namespace LVFS {
namespace Db {

EntitiesListDelegate::EntitiesListDelegate(const Interface::Adaptor<IStorage> &container, QObject *parent) :
    Delegate(parent),
    m_container(container)
{}

QWidget *EntitiesListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
        case 0:
        {
            return new QLineEdit(parent);
        }
        case 1:
        {
            EFC::ScopedPointer<QComboBox> editor(new QComboBox(parent));

            for (auto &i : m_container->entities())
                editor->addItem(toUnicode(i.second.name()), static_cast<qlonglong>(i.first));

            editor->setCurrentIndex(0);
            return editor.release();
        }
    }

    return NULL;
}

void EntitiesListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column())
    {
        case 0:
        {
            static_cast<QLineEdit*>(editor)->setText(toUnicode(static_cast<EntitiesListItem *>(index.internalPointer())->property().name));
            break;
        }
        case 1:
        {
            Storage::Entities::const_iterator idx = m_container->entities().find(static_cast<EntitiesListItem *>(index.internalPointer())->entity().id());

            if (idx != m_container->entities().end())
                static_cast<QComboBox*>(editor)->setCurrentIndex(index.row());

            break;
        }
    }
}

void EntitiesListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column())
    {
        case 0:
        {
            QString text = static_cast<QLineEdit *>(editor)->text();

            if (!text.isEmpty())
                static_cast<EntitiesListItem *>(index.internalPointer())->setName(fromUnicode(text).data());

            break;
        }
        case 1:
        {
            Storage::Entities::const_iterator idx = m_container->entities().find(static_cast<QComboBox*>(editor)->itemData(static_cast<QComboBox*>(editor)->currentIndex(), Qt::UserRole).toLongLong());

            if (idx != m_container->entities().end())
                static_cast<EntitiesListItem *>(index.internalPointer())->setEntity((*idx).second);

            break;
        }
    }
}

}}
