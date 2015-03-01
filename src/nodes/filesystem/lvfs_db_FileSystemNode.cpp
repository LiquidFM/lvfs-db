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

void FileSystemNode::accept(const Interface::Holder &view, Files &files)
{
    m_node->accept(view, files);
}

void FileSystemNode::copy(const Interface::Holder &view, const Interface::Holder &dest, Files &files, bool move)
{
    m_node->copy(view, dest, files, move);
}

void FileSystemNode::remove(const Interface::Holder &view, Files &files)
{
    m_node->remove(view, files);
}

void FileSystemNode::cancel(const Files &files)
{
    m_node->cancel(files);
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
    return m_node->node(file);
}

void FileSystemNode::setNode(const Interface::Holder &file, const Interface::Holder &node)
{
    m_node->setNode(file, node);
}

}}
