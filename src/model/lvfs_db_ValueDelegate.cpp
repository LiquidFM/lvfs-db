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

#include "lvfs_db_ValueDelegate.h"

#include "lvfs_db_ValueModel.h"
#include "items/lvfs_db_FileItem.h"
#include "items/lvfs_db_ValueItem.h"
#include "items/lvfs_db_PropertyItem.h"
#include "../gui/value/lvfs_db_EntityValueDialog.h"

#include <lvfs-core/tools/widgets/ValueDialog>
#include <QtGui/QMessageBox>


namespace LVFS {
namespace Db {

ValueDelegate::ValueDelegate(const Interface::Adaptor<IStorage> &storage, const Entity &entity, QObject *parent) :
    Delegate(parent),
    m_storage(storage),
    m_entity(entity)
{}

QWidget *ValueDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QModelIndex idx(mapToSource(index));

    if (static_cast<Item *>(idx.internalPointer())->isValue())
    {
        ValueItem *item = static_cast<ValueItem *>(idx.internalPointer());

        switch (item->value().entity().type())
        {
            case Entity::Int:
//                if (m_storage->schema(item->value().entity()) == Interface::Adaptor<IStorage>::Rating)
//                    return new Editor<typename EntityValueType<Entity::Int>::type>::type(parent);
//                else
                    return new Editor<typename EntityValueType<Entity::Int>::type>::type(parent);

            case Entity::String:
//                if (m_storage->schema(item->value().entity()) == Interface::Adaptor<IStorage>::Path)
//                    return new Editor<typename EntityValueType<Entity::String>::type>::type(parent);
//                else
                    return new Editor<typename EntityValueType<Entity::String>::type>::type(parent);

            case Entity::Date:
                return new Editor<typename EntityValueType<Entity::Date>::type>::type(parent);

            case Entity::Time:
                return new Editor<typename EntityValueType<Entity::Time>::type>::type(parent);

            case Entity::DateTime:
                return new Editor<typename EntityValueType<Entity::DateTime>::type>::type(parent);

            case Entity::Memo:
                return new Editor<typename EntityValueType<Entity::Memo>::type>::type(parent);

            case Entity::Composite:
            {
                if (m_storage->transaction())
                {
                    EntityValueDialog dialog(m_storage, item->value(), parent);

                    if (dialog.exec() != EntityValueDialog::Accepted)
                        m_storage->rollback();
                    else
                        if (m_storage->commit())
                        {
                            CompositeEntityValue(item->value()).resetValue();
                            const_cast<ValueModel *>(static_cast<const ValueModel *>(idx.model()))->update(idx);
                        }
                        else
                        {
                            m_storage->rollback();
                            QMessageBox::critical(parent, tr("Error"), toUnicode(m_storage->lastError()));
                        }
                }
                else
                    QMessageBox::critical(parent, tr("Error"), toUnicode(m_storage->lastError()));

                break;
            }

            default:
                break;
        }
    }

    return NULL;
}

void ValueDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QModelIndex idx(mapToSource(index));

    if (static_cast<Item *>(idx.internalPointer())->isValue())
    {
        ValueItem *item = static_cast<ValueItem *>(idx.internalPointer());

        switch (item->value().entity().type())
        {
            case Entity::Int:
//                if (m_storage->schema(item->value().entity()) == Interface::Adaptor<IStorage>::Rating)
//                    EditorValue<typename EntityValueType<Entity::Int>::type>::setValue(editor, index.data(Qt::DisplayRole));
//                else
                    EditorValue<typename EntityValueType<Entity::Int>::type>::setValue(editor, idx.data(Qt::DisplayRole));

                break;

            case Entity::String:
//                if (m_storage->schema(item->value().entity()) == Interface::Adaptor<IStorage>::Path)
//                    EditorValue<typename EntityValueType<Entity::String>::type>::setValue(editor, index.data(Qt::DisplayRole));
//                else
                    EditorValue<typename EntityValueType<Entity::String>::type>::setValue(editor, idx.data(Qt::DisplayRole));

                break;

            case Entity::Date:
                EditorValue<typename EntityValueType<Entity::Date>::type>::setValue(editor, idx.data(Qt::DisplayRole));
                break;

            case Entity::Time:
                EditorValue<typename EntityValueType<Entity::Time>::type>::setValue(editor, idx.data(Qt::DisplayRole));
                break;

            case Entity::DateTime:
                EditorValue<typename EntityValueType<Entity::DateTime>::type>::setValue(editor, idx.data(Qt::DisplayRole));
                break;

            case Entity::Memo:
                EditorValue<typename EntityValueType<Entity::Memo>::type>::setValue(editor, idx.data(Qt::DisplayRole));
                break;

            case Entity::Composite:
            default:
                break;
        }
    }
}

void ValueDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QModelIndex idx(mapToSource(index));

    if (static_cast<Item *>(idx.internalPointer())->isValue())
    {
        ValueItem *item = static_cast<ValueItem *>(idx.internalPointer());
        ::EFC::Variant value;

        switch (item->value().entity().type())
        {
            case Entity::Int:
                value = toVariant(EditorValue<typename EntityValueType<Entity::Int>::type>::value(editor));
                break;

            case Entity::String:
                value = toVariant(EditorValue<typename EntityValueType<Entity::String>::type>::value(editor));
                break;

            case Entity::Date:
                value = toVariant(EditorValue<typename EntityValueType<Entity::Date>::type>::value(editor));
                break;

            case Entity::Time:
                value = toVariant(EditorValue<typename EntityValueType<Entity::Time>::type>::value(editor));
                break;

            case Entity::DateTime:
                value = toVariant(EditorValue<typename EntityValueType<Entity::DateTime>::type>::value(editor));
                break;

            case Entity::Memo:
                value = toVariant(EditorValue<typename EntityValueType<Entity::Memo>::type>::value(editor));
                break;

            case Entity::Composite:
            default:
                break;
        }

        if (m_storage->transaction())
//            if (m_storage->schema(item->value().entity()) == Interface::Adaptor<IStorage>::Path)
//            {
//                QString error;
//                QueryResultPathValueItem *file = static_cast<QueryResultPathValueItem *>(item);
//                QString fileName = file->info().fileName();
//
//                if (file->info().rename(value.toString(), error))
//                    if (m_storage->updateValue(file->value(), file->info().absoluteFilePath(value.toString())))
//                        if (m_storage->commit())
//                            file->update();
//                        else
//                        {
//                            m_storage->rollback();
//                            file->info().rename(fileName, error);
//                            QMessageBox::critical(editor, tr("Error"), toUnicode(m_storage->lastError()));
//                        }
//                    else
//                    {
//                        m_storage->rollback();
//                        file->info().rename(fileName, error);
//                        QMessageBox::critical(
//                                      editor,
//                                      tr("Failed to rename file \"%1\"").arg(file->info().fileName()),
//                                      toUnicode(m_storage->lastError()));
//                    }
//                else
//                {
//                    m_storage->rollback();
//                    QMessageBox::critical(
//                            editor,
//                            tr("Failed to rename file \"%1\"").
//                            arg(file->info().fileName()),
//                            error);
//                }
//            }
//            else
                if (m_storage->updateValue(item->value(), value))
                {
                    if (m_storage->commit())
                        const_cast<ValueModel *>(static_cast<const ValueModel *>(idx.model()))->update(idx);
                    else
                    {
                        QMessageBox::critical(editor, tr("Error"), toUnicode(m_storage->lastError()));
                        m_storage->rollback();
                    }
                }
                else
                {
                    QMessageBox::critical(editor, tr("Error"), toUnicode(m_storage->lastError()));
                    m_storage->rollback();
                }
        else
            QMessageBox::critical(editor, tr("Error"), toUnicode(m_storage->lastError()));
    }
}

QModelIndex ValueDelegate::mapToSource(const QModelIndex &index) const
{
    return static_cast<const QSortFilterProxyModel *>(index.model())->mapToSource(index);
}

}}
