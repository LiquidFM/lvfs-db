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

#ifndef LVFS_DB_FILESYSTEMDIRECTORY_H_
#define LVFS_DB_FILESYSTEMDIRECTORY_H_

#include <lvfs/IDirectory>
#include <lvfs-db/IStorage>
#include <lvfs-core/INodeFactory>


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE FileSystemDirectory : public ExtendsBy<IDirectory, Core::INodeFactory>
{
public:
    FileSystemDirectory(const Interface::Adaptor<IStorage> &storage, const Interface::Holder &file);
    virtual ~FileSystemDirectory();

public: /* IFileSystemDirectory */
    virtual const_iterator begin() const;
    virtual const_iterator end() const;

    virtual bool exists(const char *name) const;
    virtual Interface::Holder entry(const char *name, const IType *type = NULL, bool create = false);

    virtual bool copy(const Progress &callback, const Interface::Holder &file, bool move = false);
    virtual bool rename(const Interface::Holder &file, const char *name);
    virtual bool remove(const Interface::Holder &file);

    virtual const Error &lastError() const;

public: /* INodeFactory */
    virtual Interface::Holder createNode(const Interface::Holder &file, const Interface::Holder &parent) const;

private:
    Interface::Adaptor<IStorage> m_storage;
    Interface::Adaptor<IDirectory> m_file;
};

}}

#endif /* LVFS_DB_FILESYSTEMDIRECTORY_H_ */
