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

#ifndef LVFS_DB_LISTENTITYDIALOG_H_
#define LVFS_DB_LISTENTITYDIALOG_H_

#include <QtGui/QDialog>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QDialogButtonBox>
#include <lvfs-core/tools/events/KeyboardEventHandler>
#include <lvfs-core/tools/events/KeyboardEventSource>
#include <lvfs-db/IStorage>
#include "model/lvfs_db_EntitiesTreeModel.h"


using namespace ::LVFS;
using namespace ::LVFS::Db;
using namespace ::LVFS::Tools;

class PLATFORM_MAKE_PRIVATE ListEntityDialog : public QDialog
{
    Q_OBJECT

public:
    ListEntityDialog(const Interface::Adaptor<IStorage> &container, QWidget *parent = 0);

    virtual void accept();

private:
    enum ActionId
    {
        Create,
        Remove,
        AddProperty,
        RemoveProperty
    };

private Q_SLOTS:
    void actionTriggered(QAction *action);

private:
    typedef KeyboardEventSource<
                EventSourceBase<
                    QTreeView
                >
            > EntitiesTreeView;
    typedef KeyboardEventHandler<
                EventHandlerBase<
                    ListEntityDialog
                >
            > EntitiesTreeViewHandler;

    void removeEntity(const QModelIndex &index);
    void removeEntity();
    void insertProperty();

private:
    void createEntity();

private:
    QModelIndex currentIndex();

private:
    Interface::Adaptor<IStorage> m_container;
    EntitiesTreeViewHandler m_handler;
    QToolBar m_toolBar;
    EntitiesTreeView m_view;
    EntitiesTreeModel m_model;
    QDialogButtonBox m_buttonBox;
    QVBoxLayout m_verticatLayout;
};

#endif /* LVFS_DB_LISTENTITYDIALOG_H_ */
