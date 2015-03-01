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

#include "lvfs_db_Plugin.h"
#include "lvfs_db_Storage.h"

#include <lvfs/IDirectory>
#include <brolly/assert.h>


namespace {
using namespace LVFS;

class Type : public IType
{
public:
    virtual const char *name() const { return "application/octet-stream"; }
    virtual Interface::Holder icon() const { return Interface::Holder(); }
    virtual const char *description() const { return "SQLite 3.x database"; }
};

}


namespace LVFS {
namespace Db {

Plugin::Plugin()
{}

Plugin::~Plugin()
{}

Interface::Holder Plugin::open(const Interface::Holder &file) const
{
    static const Type type;

    IDirectory *directory = file->as<IDirectory>();
    ASSERT(directory != NULL);
    Interface::Holder entry = directory->entry(".storage.idm", &type);

    if (entry.isValid())
    {
        Interface::Holder res(new (std::nothrow) Storage(file, entry));

        if (LIKELY(res.isValid() == true))
            if (res->as<IStorage>()->isDbValid())
                return res;
    }

    return Interface::Holder();
}

const Error &Plugin::lastError() const
{
    return m_error;
}

void Plugin::registered()
{

}

}}
