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

#include "lvfs_db_QueryResultsNode.h"
#include "../../model/items/lvfs_db_FileItem.h"
#include "../../model/items/lvfs_db_PropertyItem.h"

#include <lvfs-core/models/Qt/IView>


namespace LVFS {
namespace Db {

using namespace LiquidDb;


QueryResultsNode::QueryResultsNode(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, const Interface::Holder &parent) :
    ListValueModel(storage, reader),
    Complements(storage.interface(), parent),
    m_geometry(),
    m_sorting(0, ::Qt::AscendingOrder)
{
    ASSERT(m_sorting.first < columnCount(QModelIndex()));
}

QueryResultsNode::~QueryResultsNode()
{}

void QueryResultsNode::refresh(int depth)
{

}

void QueryResultsNode::opened(const Interface::Holder &view)
{

}

void QueryResultsNode::closed(const Interface::Holder &view)
{

}

void QueryResultsNode::accept(const Interface::Holder &view, Core::INode::Files &files)
{
    files.clear();
}

void QueryResultsNode::copy(const Interface::Holder &view, const Interface::Holder &dest, Core::INode::Files &files, bool move)
{
    ASSERT(!"Should not be reached!");
}

void QueryResultsNode::remove(const Interface::Holder &view, Core::INode::Files &files)
{

}

void QueryResultsNode::clear()
{

}

Interface::Holder QueryResultsNode::node(const Interface::Holder &file) const
{
    return Interface::Holder();
}

void QueryResultsNode::setNode(const Interface::Holder &file, const Interface::Holder &node)
{}

QAbstractItemModel *QueryResultsNode::model() const
{
    return const_cast<QueryResultsNode *>(this);
}

const QueryResultsNode::Geometry &QueryResultsNode::geometry() const
{
    return m_geometry;
}

const QueryResultsNode::Sorting &QueryResultsNode::sorting() const
{
    return m_sorting;
}

QModelIndex QueryResultsNode::currentIndex() const
{
    return m_currentIndex;
}

void QueryResultsNode::setCurrentIndex(const QModelIndex &index)
{
    m_currentIndex = index;
}

Interface::Holder QueryResultsNode::search(const QModelIndex &file, const Interface::Holder &view)
{
    return Interface::Holder();
}

Interface::Holder QueryResultsNode::activated(const QModelIndex &file, const Interface::Holder &view)
{
    Db::Item *item = static_cast<Db::Item *>(file.internalPointer());

    if (item != NULL)
        if (item->isPath())
            static_cast<FileItem *>(item)->open();
        else
            if (item->parent() == NULL && m_reader.entity().type() == Entity::Composite)
            {
                for (int i = 0, size = item->size(); i < size; ++i)
                    if (m_storage->schema(static_cast<PropertyItem *>(static_cast<Db::Item *>(item)->at(i))->entity()) == IStorage::Path)
                    {
                        view->as<Core::Qt::IView>()->select(index(static_cast<Db::Item *>(item)->at(i)), true);
                        break;
                    }
            }

    return Interface::Holder();
}

}}
