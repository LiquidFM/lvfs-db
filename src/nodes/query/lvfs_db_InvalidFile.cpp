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

#include "lvfs_db_InvalidFile.h"

#include <lvfs/Module>

#include <cstring>
#include <cstdlib>


namespace LVFS {
namespace Db {

InvalidFile::InvalidFile(const char *file) :
    m_title(::strdup(file)),
    m_type(Module::desktop().typeOfUnknownFile())
{}

InvalidFile::~InvalidFile()
{
    ::free(m_title);
}

const char *InvalidFile::title() const
{
    return m_title;
}

const char *InvalidFile::schema() const
{
    return "";
}

const char *InvalidFile::location() const
{
    return m_title;
}

const IType *InvalidFile::type() const
{
    return m_type->as<IType>();
}

}}
