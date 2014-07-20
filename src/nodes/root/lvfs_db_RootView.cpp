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

#include "lvfs_db_RootView.h"
#include "../../lvfs_db_INode.h"

#include <lvfs/IDirectory>
#include <lvfs-core/INode>
#include <lvfs-core/IMainView>

#include <brolly/assert.h>
#include <cstdlib>


namespace LVFS {
namespace Db {

RootView::RootView() :
    m_view()
{
    m_view.setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_view.setContextMenuPolicy(::Qt::DefaultContextMenu);
    m_view.setSortingEnabled(true);
}

RootView::~RootView()
{
    ASSERT(!m_node.isValid());
}

QWidget *RootView::widget() const
{
    return const_cast<QTreeView *>(&m_view);
}

void RootView::setMainView(const Interface::Holder &mainView)
{
    ASSERT(mainView.isValid());
    ASSERT(mainView->as<Core::IMainView>() != NULL);
    m_mainView = mainView;
}

const Interface::Holder &RootView::node() const
{
    return m_node;
}

bool RootView::setNode(const Interface::Holder &node)
{
    if (!node.isValid())
    {
        m_node.reset();
        return true;
    }

    return openNode(node, QModelIndex(), QModelIndex());
}

bool RootView::openNode(const Interface::Holder &node, const QModelIndex &currentIdx, const QModelIndex &parentIdx)
{
    Core::INode *coreNode = node->as<Core::INode>();

    if (Db::INode *dbNode = node->as<Db::INode>())
    {
        if (parentIdx.isValid())
            dbNode->setParentIndex(parentIdx);
        else if (currentIdx.isValid())
            m_node->as<Core::INode>()->closed(Interface::Holder::fromRawData(this));

        m_node = node;
        m_view.setModel(dbNode->model());
        coreNode->opened(Interface::Holder::fromRawData(this));

        qint32 column = 0;
        for (auto i : coreNode->geometry())
            m_view.setColumnWidth(column++, i);

        m_view.sortByColumn(coreNode->sorting().first, coreNode->sorting().second);

        coreNode->refresh(0);

        QModelIndex selected = currentIdx;

        if (selected.isValid())
            selected = dbNode->model()->index(selected.row(), selected.column());

        if (!selected.isValid())
            selected = dbNode->model()->index(0, 0);

        if (LIKELY(selected.isValid() == true))
        {
            m_view.setFocus();
            m_view.scrollTo(selected, QAbstractItemView::PositionAtCenter);
            m_view.selectionModel()->select(selected, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Columns);
            m_view.selectionModel()->setCurrentIndex(selected, QItemSelectionModel::ClearAndSelect);
        }

        return true;
    }

    return false;
}

}}
