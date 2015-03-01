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

#include "lvfs_db_FileSystemDirectory.h"
#include "lvfs_db_FileSystemNode.h"

#include <lvfs/Module>
#include <lvfs/IDirectory>
#include <lvfs-core/INodeFactory>

#include <cstring>


namespace {
using namespace LVFS;
using namespace LVFS::Core;

class Iterator : public Db::FileSystemDirectory::const_iterator
{
public:
    Iterator(const Interface::Adaptor<Db::IStorage> &storage, const const_iterator &iterator) :
        const_iterator(new (std::nothrow) Imp(storage, iterator))
    {}

protected:
    class Imp : public const_iterator::Implementation
    {
        PLATFORM_MAKE_NONCOPYABLE(Imp)
        PLATFORM_MAKE_NONMOVEABLE(Imp)

    public:
        Imp(const Interface::Adaptor<Db::IStorage> &storage, const const_iterator &iterator) :
            m_storage(storage),
            m_iterator(iterator)
        {
            if (m_iterator.isValid() && m_iterator->isValid())
                if (::strcmp((*m_iterator)->as<IEntry>()->type()->name(), Module::DirectoryTypeName) == 0)
                    m_file.reset(new (std::nothrow) Db::FileSystemDirectory(m_storage, *m_iterator));
                else
                    m_file = (*m_iterator);
        }

        virtual ~Imp()
        {}

        virtual bool isEqual(const Holder &other) const
        {
            return m_iterator == other.as<Imp>()->m_iterator;
        }

        virtual reference asReference() const
        {
            return m_file;
        }

        virtual pointer asPointer() const
        {
            return &m_file;
        }

        virtual void next()
        {
            m_file.reset();

            if ((++m_iterator)->isValid())
                if (::strcmp((*m_iterator)->as<IEntry>()->type()->name(), Module::DirectoryTypeName) == 0)
                    m_file.reset(new (std::nothrow) Db::FileSystemDirectory(m_storage, *m_iterator));
                else
                    m_file = (*m_iterator);
        }

    private:
        Interface::Adaptor<Db::IStorage> m_storage;
        const_iterator m_iterator;
        Interface::Holder m_file;
    };
};

}


namespace LVFS {
namespace Db {

FileSystemDirectory::FileSystemDirectory(const Interface::Adaptor<IStorage> &storage, const Interface::Holder &file) :
    ExtendsBy(file),
    m_storage(storage),
    m_file(file)
{}

FileSystemDirectory::~FileSystemDirectory()
{}

FileSystemDirectory::const_iterator FileSystemDirectory::begin() const
{
    return Iterator(m_storage, m_file->begin());
}

FileSystemDirectory::const_iterator FileSystemDirectory::end() const
{
    return Iterator(m_storage, m_file->end());
}

bool FileSystemDirectory::exists(const char *name) const
{
    return m_file->exists(name);
}

Interface::Holder FileSystemDirectory::entry(const char *name, const IType *type, bool create)
{
    return m_file->entry(name, type, create);
}

bool FileSystemDirectory::copy(const Progress &callback, const Interface::Holder &file, bool move)
{
    return m_file->copy(callback, file, move);
}

bool FileSystemDirectory::rename(const Interface::Holder &file, const char *name)
{
    return m_file->rename(file, name);
}

bool FileSystemDirectory::remove(const Interface::Holder &file)
{
    return m_file->remove(file);
}

const Error &FileSystemDirectory::lastError() const
{
    return m_file->lastError();
}

Interface::Holder FileSystemDirectory::createNode(const Interface::Holder &file, const Interface::Holder &parent) const
{
    Interface::Holder node(original()->as<Core::INodeFactory>()->createNode(file, parent));

    if (LIKELY(node.isValid()))
        return Interface::Holder(new (std::nothrow) FileSystemNode(m_storage, node));

    return Interface::Holder();
}

}}
