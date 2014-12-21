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

#include "lvfs_db_CompositeValuePossibleDirItem.h"
#include "lvfs_db_CompositeValuePossibleFileItem.h"

#include <lvfs-core/models/Qt/SortFilterModel>


namespace LVFS {
namespace Db {

class CompositeValueFakePossibleDirItem : public CompositeValuePossibleDirItem
{
public:
    typedef QList<Model::Item *> Container;

public:
    CompositeValueFakePossibleDirItem(const Interface::Holder &source, Model::Item *parent = 0) :
        CompositeValuePossibleDirItem(EntityValue(), source, parent)
    {}

    /* Base */
    virtual QVariant data(qint32 column, qint32 role) const
    {
//        switch (role)
//        {
//            case Qt::EditRole:
//            case Qt::DisplayRole:
//                return source()->info()->fileName().as<QString>();
//            case Qt::DecorationRole:
//                return source()->info()->fileType()->icon();
//            case Qt::TextAlignmentRole:
//                return Qt::AlignLeft;
//            case Qt::ToolTipRole:
//                return source()->info()->fileType()->name();
//        }

        return QVariant();
    }
};


class CompositeValueFakePossibleFileItem : public CompositeValuePossibleFileItem
{
public:
    CompositeValueFakePossibleFileItem(const Interface::Holder &source, Model::Item *parent = 0) :
        CompositeValuePossibleFileItem(EntityValue(), source, parent)
    {}

    /* Base */
    virtual QVariant data(qint32 column, qint32 role) const
    {
//        switch (role)
//        {
//            case Qt::EditRole:
//            case Qt::DisplayRole:
//                return source()->info()->fileName().as<QString>();
//            case Qt::DecorationRole:
//                return source()->info()->fileType()->icon();
//            case Qt::TextAlignmentRole:
//                return Qt::AlignLeft;
//            case Qt::ToolTipRole:
//                return source()->info()->fileType()->name();
//        }

        return QVariant();
    }
};

static bool lessThan(CompositeValuePossibleDirItem::Container::value_type v1, CompositeValuePossibleDirItem::Container::value_type v2)
{
    if (static_cast<CompositeValuePathItem *>(v1)->isFile())
        if (static_cast<CompositeValuePathItem *>(v2)->isFile())
            return Core::Qt::SortFilterModel::compareFileNames(static_cast<CompositeValuePathItem *>(v1)->fileName(), static_cast<CompositeValuePathItem *>(v2)->fileName());
        else
            return true;
    else
        if (static_cast<CompositeValuePathItem *>(v2)->isFile())
            return false;
        else
            return Core::Qt::SortFilterModel::compareFileNames(static_cast<CompositeValuePathItem *>(v1)->fileName(), static_cast<CompositeValuePathItem *>(v2)->fileName());
}

CompositeValuePossibleDirItem::CompositeValuePossibleDirItem(const EntityValue &value, const Interface::Holder &source, Model::Item *parent) :
    CompositeValuePathItem(value, parent),
    m_source(source)
{
//    const Interface::Holder &file;
//
//    for (SnapshotItem::const_iterator i = source->begin(), end = source->end(); i != end; ++i)
//    {
//        file = (*i);
//
//        if (file->info()->isFile())
//            add(new CompositeValueFakePossibleFileItem(file, this));
//        else
//            add(new CompositeValueFakePossibleDirItem(file, this));
//    }
//
//    qSort(m_items.begin(), m_items.end(), lessThan);
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
//    switch (role)
//    {
//        case Qt::EditRole:
//        case Qt::DisplayRole:
//            return toQVariant(m_value.value());
//        case Qt::DecorationRole:
//            return m_source->info()->fileType()->icon();
//        case Qt::TextAlignmentRole:
//            return Qt::AlignLeft;
//        case Qt::ToolTipRole:
//            return m_source->info()->fileType()->name();
//    }

    return QVariant();
}

QString CompositeValuePossibleDirItem::fileName() const
{
    return QString(); //m_source->info()->fileName();
}

bool CompositeValuePossibleDirItem::isFile() const
{
    return false;
}

void CompositeValuePossibleDirItem::open() const
{}

}}
