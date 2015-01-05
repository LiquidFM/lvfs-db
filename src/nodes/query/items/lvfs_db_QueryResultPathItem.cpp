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

#include "lvfs_db_QueryResultPathItem.h"
#include "../lvfs_db_InvalidFile.h"
#include "../../../lvfs_db_common.h"

#include <lvfs/IEntry>
#include <lvfs/IDirectory>
#include <QtGui/QIcon>


namespace LVFS {
namespace Db {

//QueryResultPathItem::QueryResultPathItem(IFileInfo::Holder &info, Item *parent) :
//    QueryResultItem(parent),
//    m_info(info.take()),
//    m_location(m_info->fileName()),
//    m_node(NULL)
//{}

QueryResultPathItem::QueryResultPathItem(const Interface::Adaptor<IStorage> &container, const QString &fileName, Item *parent) :
    QueryResultItem(parent),
    m_file(container.interface()->as<IDirectory>()->entry(fromUnicode(fileName)))
//    m_info(new InvalidInfo(fileName)),
//    m_location(m_info->fileName()),
//    m_node(NULL)
{
    if (!m_file.isValid())
        m_file.reset(new (std::nothrow) InvalidFile(fromUnicode(fileName)));
}

QueryResultPathItem::~QueryResultPathItem()
{
    for (auto i : m_items)
        delete i;
}

QueryResultPathItem::Item *QueryResultPathItem::at(size_type index) const
{
    return m_items.at(index);
}

QueryResultPathItem::size_type QueryResultPathItem::size() const
{
    return m_items.size();
}

QueryResultPathItem::size_type QueryResultPathItem::indexOf(Item *item) const
{
    for (auto i = m_items.begin(), end = m_items.end(); i != end; ++i)
        if (*i == item)
            return i - m_items.begin();

    return InvalidIndex;
}

QVariant QueryResultPathItem::data(qint32 column, qint32 role) const
{
    switch (role)
    {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return toUnicode(m_file->as<IEntry>()->title());
        case Qt::DecorationRole:
//            if (isLocked())
//                return lockIcon();
//            else
        {
            QIcon icon;
            icon.addFile(toUnicode(m_file->as<IEntry>()->type()->icon()->as<IEntry>()->location()), QSize(16, 16));
            return icon;
        }
        case Qt::TextAlignmentRole:
            return Qt::AlignLeft;
        case Qt::ToolTipRole:
//            if (isLocked())
//                return lockReason();
//            else
                break;
    }

    return QVariant();
}

bool QueryResultPathItem::isRoot()
{
    return false;
}

bool QueryResultPathItem::isProperty()
{
    return false;
}

bool QueryResultPathItem::isValue()
{
    return false;
}

bool QueryResultPathItem::isPath()
{
    return true;
}

bool QueryResultPathItem::isPathProperty()
{
    return false;
}

}}
