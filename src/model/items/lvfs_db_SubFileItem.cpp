/**
 * This file is part of lvfs-core.
 *
 * Copyright (C) 2011-2015 Dmitriy Vilkov, <dav.daemon@gmail.com>
 *
 * lvfs-core is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lvfs-core is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lvfs-core. If not, see <http://www.gnu.org/licenses/>.
 */

#include "lvfs_db_SubFileItem.h"

#include <lvfs/Module>
#include <lvfs/IEntry>
#include <lvfs/IDirectory>
#include <lvfs/IApplication>
#include <lvfs/IApplications>
#include <brolly/assert.h>

#include <cstring>


namespace LVFS {
namespace Db {

SubFileItem::SubFileItem(const Interface::Holder &file, Item *parent) :
    Item(parent),
    m_file(file)
{
    ASSERT(m_file.isValid());
    init();
}

SubFileItem::SubFileItem(const EntityValue &value, const Interface::Holder &file, Item *parent) :
    Item(parent),
    m_file(file)
{
    if (m_file.isValid())
        init();
    else
        init(value);
}

SubFileItem::~SubFileItem()
{}

QVariant SubFileItem::data(qint32 column, qint32 role) const
{
    switch (role)
    {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return m_name;
        case Qt::DecorationRole:
            return m_icon;
        case Qt::TextAlignmentRole:
            return Qt::AlignLeft;
        case Qt::ToolTipRole:
            return m_toolTip;
    }

    return QVariant();
}

bool SubFileItem::isPath() const
{
    return true;
}

void SubFileItem::open() const
{
    if (::strcmp(m_file->as<IEntry>()->type()->name(), Module::DirectoryTypeName) != 0)
    {
        Interface::Holder apps = Module::desktop().applications(m_file->as<IEntry>()->type());

        if (apps.isValid())
        {
            ASSERT(apps->as<IApplications>() != NULL);
            IApplications::const_iterator iterator = apps->as<IApplications>()->begin();

            if (iterator != apps->as<IApplications>()->end())
            {
                ASSERT((*iterator)->as<IApplication>() != NULL);
                (*iterator)->as<IApplication>()->open(m_file->as<IEntry>());
            }
        }
    }
}

void SubFileItem::init()
{
    m_name = toUnicode(m_file->as<IEntry>()->title());
    m_icon.addFile(toUnicode(m_file->as<IEntry>()->type()->icon()->as<IEntry>()->location()), QSize(16, 16));
    m_toolTip = toUnicode(m_file->as<IEntry>()->type()->name());

    if (IDirectory *dir = m_file->as<IDirectory>())
        for (IDirectory::const_iterator i = dir->begin(), end = dir->end(); i != end; ++i)
            m_items.push_back(new SubFileItem(*i, this));
}

void SubFileItem::init(const EntityValue &value)
{
    m_name = toUnicode(value.value().asString());
    m_icon.addFile(toUnicode(Module::desktop().typeOfUnknownFile()->as<IType>()->icon()->as<IEntry>()->location()), QSize(16, 16));
    m_toolTip = tr("File does not exists!");
}

}}
