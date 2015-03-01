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

#include "lvfs_db_CompositeValuePossibleDirItem.h"
#include "lvfs_db_CompositeValuePossibleFileItem.h"
#include "../../../../lvfs_db_common.h"

#include <lvfs/IEntry>
#include <lvfs/Module>
#include <lvfs/IDirectory>
#include <lvfs-core/models/Qt/SortFilterModel>

#include <cstring>

namespace LVFS {
namespace Db {

static bool lessThan(CompositeValuePossibleDirItem::Container::value_type v1, CompositeValuePossibleDirItem::Container::value_type v2)
{
    if (static_cast<CompositeValuePathItem *>(v1)->isFile())
        if (static_cast<CompositeValuePathItem *>(v2)->isFile())
            return Core::Qt::SortFilterModel::compareFileNames(static_cast<CompositeValuePathItem *>(v1)->fileName(), static_cast<CompositeValuePathItem *>(v2)->fileName());
        else
            return false;
    else
        if (static_cast<CompositeValuePathItem *>(v2)->isFile())
            return true;
        else
            return Core::Qt::SortFilterModel::compareFileNames(static_cast<CompositeValuePathItem *>(v1)->fileName(), static_cast<CompositeValuePathItem *>(v2)->fileName());
}

CompositeValuePossibleDirItem::CompositeValuePossibleDirItem(const EntityValue &value, const Interface::Holder &source, Model::Item *parent) :
    CompositeValuePathItem(value, parent),
    m_source(source),
    m_name(toUnicode(source->as<IEntry>()->title())),
    m_toolTip(toUnicode(source->as<IEntry>()->type()->name())),
    m_icon()
{
    m_icon.addFile(toUnicode(source->as<IEntry>()->type()->icon()->as<IEntry>()->location()), QSize(16, 16));

    for (auto i = m_source->as<IDirectory>()->begin(), end = m_source->as<IDirectory>()->end(); i != end; ++i)
    {
        const Interface::Holder &file = (*i);

        if (::strcmp(file->as<IEntry>()->type()->name(), Module::DirectoryTypeName) != 0)
            add(new CompositeValuePossibleFileItem(EntityValue(), file, this));
        else
            add(new CompositeValuePossibleDirItem(EntityValue(), file, this));
    }

    qSort(m_items.begin(), m_items.end(), lessThan);
}

CompositeValuePossibleDirItem::~CompositeValuePossibleDirItem()
{
    qDeleteAll(m_items);
}

Model::Item *CompositeValuePossibleDirItem::at(size_type index) const
{
    return m_items.at(index);
}

CompositeValuePossibleDirItem::size_type CompositeValuePossibleDirItem::size() const
{
    return m_items.size();
}

CompositeValuePossibleDirItem::size_type CompositeValuePossibleDirItem::indexOf(Model::Item *item) const
{
    return m_items.indexOf(item);
}

QVariant CompositeValuePossibleDirItem::data(qint32 column, qint32 role) const
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

QString CompositeValuePossibleDirItem::fileName() const
{
    return m_name;
}

bool CompositeValuePossibleDirItem::isFile() const
{
    return false;
}

void CompositeValuePossibleDirItem::open() const
{}

}}
