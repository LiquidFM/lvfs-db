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
    m_view(&m_eventHandler),
    m_eventHandler(this)
{
    m_view.setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_view.setContextMenuPolicy(::Qt::DefaultContextMenu);
    m_view.setSortingEnabled(true);

    m_eventHandler.registerMouseDoubleClickEventHandler(&RootView::goIntoShortcut);
    m_eventHandler.registerShortcut(::Qt::NoModifier, ::Qt::Key_Return,    &RootView::goIntoShortcut);
    m_eventHandler.registerShortcut(::Qt::NoModifier, ::Qt::Key_Enter,     &RootView::goIntoShortcut);
    m_eventHandler.registerShortcut(::Qt::NoModifier, ::Qt::Key_Backspace, &RootView::goUpShortcut);
    m_eventHandler.registerShortcut(::Qt::NoModifier, ::Qt::Key_F2,        &RootView::renameShortcut);
    m_eventHandler.registerShortcut(::Qt::NoModifier, ::Qt::Key_F8,        &RootView::createFileShortcut);
    m_eventHandler.registerShortcut(::Qt::NoModifier, ::Qt::Key_Delete,    &RootView::removeShortcut);
    m_eventHandler.registerShortcut(::Qt::CTRL,       ::Qt::Key_F,         &RootView::searchShortcut);
    m_eventHandler.registerShortcut(::Qt::NoModifier, ::Qt::Key_Insert,    &RootView::insertShortcut);
}

RootView::~RootView()
{}

QWidget *RootView::widget() const
{
    return const_cast<TreeView *>(&m_view);
}

const Interface::Holder &RootView::mainView() const
{
    return m_mainView;
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

    Core::INode *coreNode = node->as<Core::INode>();

    if (Db::INode *dbNode = node->as<Db::INode>())
    {
        m_node = node;
        m_view.setModel(dbNode->model());
        m_view.sortByColumn(dbNode->sorting().first, dbNode->sorting().second);

        return true;
    }

    return false;
}

QModelIndex RootView::currentIndex() const
{
    return m_view.selectionModel()->currentIndex();
}

void RootView::select(const QModelIndex &index, bool expand)
{
    QModelIndex toBeSelected = index;

    if (!toBeSelected.isValid())
        toBeSelected = m_view.model()->index(0, 0);

    if (LIKELY(toBeSelected.isValid() == true))
    {
        m_view.setFocus();
        m_view.scrollTo(toBeSelected, QAbstractItemView::PositionAtCenter);
        m_view.selectionModel()->select(toBeSelected, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Columns);
        m_view.selectionModel()->setCurrentIndex(toBeSelected, QItemSelectionModel::ClearAndSelect);

        if (expand)
            m_view.expand(toBeSelected);
    }
}

void RootView::goUpShortcut()
{
    const Interface::Holder &node = m_node->as<Core::INode>()->parent();

    if (node.isValid())
        m_mainView->as<Core::IMainView>()->show(Interface::Holder::fromRawData(this), node);
}

void RootView::goIntoShortcut()
{
    QModelIndex index = m_view.selectionModel()->currentIndex();

    if (index.isValid())
    {
        Interface::Holder newNode = m_node->as<Db::INode>()->activated(Interface::Holder::fromRawData(this), index);

        if (newNode.isValid())
            m_mainView->as<Core::IMainView>()->show(Interface::Holder::fromRawData(this), newNode);
    }
}

void RootView::renameShortcut()
{

}

void RootView::createFileShortcut()
{

}

void RootView::removeShortcut()
{
    QModelIndex index = m_view.selectionModel()->currentIndex();

    if (index.isValid())
        m_node->as<Db::INode>()->remove(Interface::Holder::fromRawData(this), index);
}

void RootView::searchShortcut()
{
    QModelIndex index = m_view.selectionModel()->currentIndex();

    if (index.isValid())
    {
        Interface::Holder newNode = m_node->as<Db::INode>()->search(Interface::Holder::fromRawData(this), index);

        if (newNode.isValid())
            m_mainView->as<Core::IMainView>()->show(Interface::Holder::fromRawData(this), newNode);
    }
}

void RootView::insertShortcut()
{
    QModelIndex index = m_view.selectionModel()->currentIndex();

    if (index.isValid())
        m_node->as<Db::INode>()->insert(Interface::Holder::fromRawData(this), index);
}

}}
