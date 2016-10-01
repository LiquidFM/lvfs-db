/**
 * This file is part of lvfs-db.
 *
 * Copyright (C) 2011-2016 Dmitriy Vilkov, <dav.daemon@gmail.com>
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

#include "lvfs_db_Package.h"
#include "lvfs_db_Plugin.h"

#include <lvfs/Module>
#include <lvfs/plugins/Package>


namespace LVFS {
namespace Db {

Package::Package()
{}

Package::~Package()
{}

const char *Package::name() const
{
    return "DB";
}

Settings::Scope *Package::settings() const
{
    return NULL;
}

const Package::Plugin **Package::contentPlugins() const
{
    static const Db::Plugin plugin;
    static const Plugin types[] =
    {
        { Module::DirectoryTypeName, plugin }
    };
    enum { Count = sizeof(types) / sizeof(Plugin) };

    static const Plugin *res[Count + 1] = {};

    for (unsigned i = 0; i < Count; ++i)
        res[i] = &types[i];

    return res;
}

const Package::Plugin **Package::protocolPlugins() const
{
    return NULL;
}

}}


DECLARE_PLUGINS_PACKAGE(::LVFS::Db::Package)
