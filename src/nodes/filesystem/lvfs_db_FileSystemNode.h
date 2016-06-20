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

#ifndef LVFS_DB_FILESYSTEMNODE_H_
#define LVFS_DB_FILESYSTEMNODE_H_

#include <lvfs-core/INode>
#include <lvfs-db/IStorage>
#include <QtCore/QCoreApplication>


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE FileSystemNode : public ExtendsBy<Core::INode>
{
    Q_DECLARE_TR_FUNCTIONS(FileSystemNode)

public:
    FileSystemNode(const Interface::Adaptor<IStorage> &storage, const Interface::Holder &node);
    virtual ~FileSystemNode();

public: /* Core::INode */
    virtual const Interface::Holder &parent() const;
    virtual const Interface::Holder &file() const;

    virtual void refresh();
    virtual void opened(const Interface::Holder &view);
    virtual void closed(const Interface::Holder &view);
    virtual Interface::Holder accept(const Interface::Holder &view, Files &files);

    virtual int refs() const;
    virtual void incRef();
    virtual int decRef();
    virtual void clear();

    virtual Interface::Holder node(const Interface::Holder &file) const;
    virtual void setNode(const Interface::Holder &file, const Interface::Holder &node);

private:
    Interface::Adaptor<IStorage> m_storage;
    Interface::Adaptor<Core::INode> m_node;
};

}}

#endif /* LVFS_DB_FILESYSTEMNODE_H_ */
