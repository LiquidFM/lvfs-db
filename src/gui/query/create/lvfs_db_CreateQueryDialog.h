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

#ifndef LVFS_DB_CREATEQUERYDIALOG_H_
#define LVFS_DB_CREATEQUERYDIALOG_H_

#include <QtGui/QDialog>
#include <QtGui/QToolBar>
#include <QtGui/QSplitter>
#include <QtGui/QTreeView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QDialogButtonBox>
#include <lvfs/Interface>
#include <lvfs-core/tools/events/KeyboardEventHandler>
#include <lvfs-core/tools/events/KeyboardEventSource>
#include <lvfs-core/tools/events/MouseEventHandler>
#include <lvfs-core/tools/events/MouseEventSource>
#include <lvfs-db/IStorage>
#include "model/lvfs_db_QueryEntitiesModel.h"
#include "model/lvfs_db_QueryConstraintsModel.h"
#include "model/lvfs_db_QueryConstraintsDelegate.h"


using namespace ::LVFS;
using namespace ::LVFS::Db;
using namespace ::LVFS::Tools;
using namespace ::LiquidDb;

class PLATFORM_MAKE_PRIVATE CreateQueryDialog : public QDialog
{
    Q_OBJECT

public:
    CreateQueryDialog(const Interface::Adaptor<IStorage> &container, const Entity &entity, QWidget *parent = 0);
    virtual ~CreateQueryDialog();

    const Entity &entity() const { return m_entity; }
    BaseConstraint::Holder constraint();
    virtual void accept();

private:
    void save();
    void load();

private:
    enum ActionId
    {
        AddGroup,
        AddConstraint,
        RemoveGroupOrConstraint
    };

private Q_SLOTS:
    void actionTriggered(QAction *action);

private:
    typedef KeyboardEventSource<
                MouseDoubleClickEventSource<
                    EventSourceBase<
                        QTreeView
                    >
                >
            > EntitiesTreeView;
    typedef KeyboardEventHandler<
                MouseDoubleClickEventHandler<
                    EventHandlerBase<
                        CreateQueryDialog
                    >
                >
            > EntitiesTreeViewHandler;

private:
    QModelIndex currentIndex1();
    QModelIndex currentIndex2();
    void addConstraint();
    void removeGroupOrConstraint();

private:
    QVBoxLayout m_verticatLayout;
    QHBoxLayout m_horizontalLayout;
    QSplitter m_splitter;
    Interface::Adaptor<IStorage> m_container;
    const Entity &m_entity;
    EntitiesTreeViewHandler m_handler1;
    EntitiesTreeViewHandler m_handler2;
    QToolBar m_toolBar1;
    QToolBar m_toolBar2;
    EntitiesTreeView m_view1;
    QueryEntitiesModel m_model;
    EntitiesTreeView m_view2;
    QueryConstraintsModel m_model2;
    QueryConstraintsDelegate m_delegate2;
    QDialogButtonBox m_buttonBox;
};

#endif /* LVFS_DB_CREATEQUERYDIALOG_H_ */
