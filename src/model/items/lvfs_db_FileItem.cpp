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

#include "lvfs_db_FileItem.h"

#include <lvfs/IDirectory>


namespace LVFS {
namespace Db {

FileItem::FileItem(const EntityValue &value, const Interface::Holder &file, Item *parent) :
    ValueItem(value, parent),
    m_item(value, file, this)
{}

FileItem::~FileItem()
{}

bool FileItem::refresh(const Interface::Adaptor<IStorage> &storage)
{
    if (!file().isValid())
    {
        Interface::Holder file = storage->file()->as<IDirectory>()->entry(value().value().asString());

        if (file.isValid())
        {
            m_item = SubFileItem(value(), file, this);
            return true;
        }
    }

    return false;
}

QVariant FileItem::data(qint32 column, qint32 role) const
{
    return m_item.data(column, role);
}

bool FileItem::isPath() const
{
    return true;
}

void FileItem::open() const
{
    return m_item.open();
}

Model::Item *FileItem::at(size_type index) const
{
    return m_item.at(index);
}

FileItem::size_type FileItem::size() const
{
    return m_item.size();
}

FileItem::size_type FileItem::indexOf(Model::Item *item) const
{
    return m_item.indexOf(item);
}

}}
