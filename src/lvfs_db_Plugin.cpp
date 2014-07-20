/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2014 Dmitriy Vilkov, <dav.daemon@gmail.com>
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


namespace LVFS {
namespace Db {

Plugin::Plugin()
{}

Plugin::~Plugin()
{}

Interface::Holder Plugin::open(const Interface::Holder &file) const
{
    IDirectory *directory = file->as<IDirectory>();
    ASSERT(directory != NULL);
    Interface::Holder entry = directory->entry(".storage.idm");

    if (entry.isValid())
        return Interface::Holder(new (std::nothrow) Storage(file, entry));

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
