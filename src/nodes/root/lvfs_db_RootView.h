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

#ifndef LVFS_DB_ROOTVIEW_H_
#define LVFS_DB_ROOTVIEW_H_

#include <QtGui/QTreeView>
#include <lvfs-core/IView>

#include <lvfs-core/models/Qt/IView>
#include <lvfs-core/tools/events/ContextMenuEventHandler>
#include <lvfs-core/tools/events/ContextMenuEventSource>
#include <lvfs-core/tools/events/KeyboardEventHandler>
#include <lvfs-core/tools/events/KeyboardEventSource>
#include <lvfs-core/tools/events/MouseEventHandler>
#include <lvfs-core/tools/events/MouseEventSource>


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE RootView : public Implements<Core::IView, Core::Qt::IView>
{
public:
    RootView();
    virtual ~RootView();

    /* Core::IView */
    virtual QWidget *widget() const;

    virtual const Interface::Holder &mainView() const;
    virtual void setMainView(const Interface::Holder &mainView);

    virtual const Interface::Holder &node() const;
    virtual void setNode(const Interface::Holder &node);

    virtual bool isAbleToView(const Interface::Holder &node) const;

    /* Core::Qt::IView */
    virtual QModelIndex currentIndex() const;
    virtual void select(const QModelIndex &index, bool expand = false);

private:
    void goUpShortcut();
    void goIntoShortcut();
    void newWindowOnOppositeTabShortcut();
    void renameShortcut();
    void createFileShortcut();
    void removeShortcut();
    void searchShortcut();
    void insertShortcut();

private:
    typedef Tools::MouseDoubleClickEventSource<
                Tools::ContextMenuEventSource<
                    Tools::KeyboardEventSource<
                        Tools::EventSourceBase<
                            QTreeView
                        >
                    >
                >
            > TreeView;

    typedef Tools::MouseDoubleClickEventHandler<
                Tools::KeyboardEventHandler<
                    Tools::EventHandlerBase<RootView>
                >
            > EventHandler;

private:
    Interface::Holder m_node;
    Interface::Holder m_mainView;

private:
    TreeView m_view;
    EventHandler m_eventHandler;
};

}}

#endif /* LVFS_DB_ROOTVIEW_H_ */
