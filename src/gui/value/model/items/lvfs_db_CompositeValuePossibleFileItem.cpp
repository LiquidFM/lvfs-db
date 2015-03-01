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

#include "lvfs_db_CompositeValuePossibleFileItem.h"
#include "../../../../lvfs_db_common.h"

#include <lvfs/IEntry>


namespace LVFS {
namespace Db {

CompositeValuePossibleFileItem::CompositeValuePossibleFileItem(const EntityValue &value, const Interface::Holder &source, Model::Item *parent) :
    CompositeValuePathItem(value, parent),
    m_source(source),
    m_name(toUnicode(m_source->as<IEntry>()->title())),
    m_toolTip(toUnicode(m_source->as<IEntry>()->type()->name())),
    m_icon()
{
    m_icon.addFile(toUnicode(m_source->as<IEntry>()->type()->icon()->as<IEntry>()->location()), QSize(16, 16));
}

QVariant CompositeValuePossibleFileItem::data(qint32 column, qint32 role) const
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

QString CompositeValuePossibleFileItem::fileName() const
{
    return m_name;
}

bool CompositeValuePossibleFileItem::isFile() const
{
    return true;
}

void CompositeValuePossibleFileItem::open() const
{
//    Application::open(m_source->container(), m_source->info());
}

}}
