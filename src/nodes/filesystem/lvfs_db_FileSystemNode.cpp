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

#include "lvfs_db_FileSystemNode.h"
#include "../../model/lvfs_db_ValueModel.h"
#include "../../gui/choose/lvfs_db_ChooseEntityDialog.h"
#include "../../gui/value/lvfs_db_EntityValueDialog.h"
#include "../../lvfs_db_common.h"

#include <lvfs/Module>
#include <lvfs/IEntry>
#include <lvfs-core/IView>
#include <lvfs-core/INodeFactory>
#include <QtGui/QMessageBox>

#include <cstdio>


namespace LVFS {
namespace Db {

FileSystemNode::FileSystemNode(const Interface::Adaptor<IStorage> &storage, const Interface::Holder &node) :
    ExtendsBy(node),
    m_storage(storage),
    m_node(node)
{}

FileSystemNode::~FileSystemNode()
{}

const Interface::Holder &FileSystemNode::parent() const
{
    return m_node->parent();
}

const Interface::Holder &FileSystemNode::file() const
{
    return m_node->file();
}

void FileSystemNode::refresh(int depth)
{
    m_node->refresh(depth);
}

void FileSystemNode::opened(const Interface::Holder &view)
{
    m_node->opened(view);
}

void FileSystemNode::closed(const Interface::Holder &view)
{
    m_node->closed(view);
}

Interface::Holder FileSystemNode::accept(const Interface::Holder &view, Files &files)
{
    using namespace LiquidDb;
    Interface::Holder res = m_node->accept(view, files);

    if (!res.isValid())
        return Interface::Holder();

    if (m_storage->transaction())
    {
        Entity entity(ChooseEntityDialog::chooseFile(m_storage, view->as<Core::IView>()->widget()));

        if (entity.isValid())
        {
            EntityValue value(m_storage->addValue(entity));

            if (value.isValid())
            {
                Entity path;
                EntityValue::List list;
                ValueModel::Files dbFiles;
                char buffer[Module::MaxUriLength];
                char prefix[Module::MaxUriLength];

                IEntry *storageEntry = m_storage->file()->as<IEntry>();
                const char *filePath = file()->as<IEntry>()->location();

                if (::strcmp(filePath, storageEntry->location()) == 0)
                    prefix[0] = 0;
                else
                {
                    if (UNLIKELY(std::snprintf(prefix, sizeof(prefix), "%s/", filePath + ::strlen(storageEntry->location()) + 1) < 0))
                    {
                        m_storage->rollback();
                        return Interface::Holder();
                    }
                }

                for (auto &i : entity.properties())
                    if (m_storage->schema(path = i.second.entity) == IStorage::Path)
                    {
                        EntityValue localValue;

                        for (auto i = files.begin(), end = files.end(); i != end; ++i)
                        {
                            if (UNLIKELY(std::snprintf(buffer, sizeof(buffer), "%s%s", prefix, (*i)->as<IEntry>()->title()) < 0))
                            {
                                m_storage->rollback();
                                return Interface::Holder();
                            }

                            localValue = m_storage->addValue(path, buffer);

                            if (localValue.isValid())
                            {
                                list.push_back(localValue);
                                dbFiles[localValue.id()] = (*i);
                            }
                            else
                            {
                                QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_storage->lastError()));
                                m_storage->rollback();
                                return Interface::Holder();
                            }
                        }

                        break;
                    }

                if (m_storage->addValue(value, list))
                {
                    EntityValueDialog dialog(m_storage, value, dbFiles, view->as<Core::IView>()->widget());

                    if (dialog.exec() != EntityValueDialog::Accepted)
                        m_storage->rollback();
                    else
                        if (m_storage->commit())
                            return res;
                        else
                        {
                            QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_storage->lastError()));
                            m_storage->rollback();
                        }

                    m_storage->setEditorGeometry(entity, fromQRect(dialog.geometry()));
                }
                else
                {
                    QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_storage->lastError()));
                    m_storage->rollback();
                }
            }
            else
                QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_storage->lastError()));
        }
    }
    else
        QMessageBox::critical(view->as<Core::IView>()->widget(), tr("Error"), toUnicode(m_storage->lastError()));

    return Interface::Holder();
}

int FileSystemNode::refs() const
{
    return m_node->refs();
}

void FileSystemNode::incRef()
{
    m_node->incRef();
}

int FileSystemNode::decRef()
{
    return m_node->decRef();
}

void FileSystemNode::clear()
{
    m_node->clear();
}

Interface::Holder FileSystemNode::node(const Interface::Holder &file) const
{
    Interface::Holder node(m_node->node(file));

    if (!node.isValid())
    {
        node = file->as<Core::INodeFactory>()->createNode(file, Interface::Holder::fromRawData(const_cast<FileSystemNode *>(this)));

        if (LIKELY(node.isValid()))
            return Interface::Holder(new (std::nothrow) FileSystemNode(m_storage, node));
    }

    return node;
}

void FileSystemNode::setNode(const Interface::Holder &file, const Interface::Holder &node)
{
    m_node->setNode(file, node);
}

}}
