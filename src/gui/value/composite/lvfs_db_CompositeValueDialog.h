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

#ifndef LVFS_DB_COMPOSITEVALUEDIALOG_H_
#define LVFS_DB_COMPOSITEVALUEDIALOG_H_

#include <lvfs-core/tools/widgets/NestedPlainDialog>
#include "widgets/lvfs_db_CompositeValueWidget.h"


class PLATFORM_MAKE_PRIVATE CompositeValueDialog : public NestedPlainDialog
{
    Q_OBJECT

public:
    CompositeValueDialog(const Interface::Adaptor<IStorage> &container, const EntityValue &value, QWidget *parent = 0);
    CompositeValueDialog(const Interface::Adaptor<IStorage> &container, const EntityValue &value, const CompositeValueModel::Files &files, QWidget *parent = 0);

protected:
    virtual void addValue();
    virtual void removeValue();

protected:
    QModelIndex currentIndex() const { return m_mainWidget.currentIndex(); }

    const Interface::Adaptor<IStorage> &container() const { return m_mainWidget.container(); }
    Interface::Adaptor<IStorage> &container() { return m_mainWidget.container(); }

    const CompositeValueModel &model() const { return m_mainWidget.model(); }
    CompositeValueModel &model() { return m_mainWidget.model(); }

    void doOpenFile(const QModelIndex &index) { m_mainWidget.open(index); }
    void doAddValue(const QModelIndex &index) { m_mainWidget.addValue(index); }
    void doRemoveValue(const QModelIndex &index) { m_mainWidget.removeValue(index); }
    void doEdit(const QModelIndex &index) { m_mainWidget.edit(index); }

private:
    void openFile1();
    void openFile2();
    void edit();

private:
    typedef MouseDoubleClickEventHandler<
                KeyboardEventHandler<
                    EventHandlerBase<
                        CompositeValueDialog
                    >
                >
            > TreeViewHandler;

private:
    TreeViewHandler m_handler;
    MainCompositeValueWidget m_mainWidget;
};

#endif /* LVFS_DB_COMPOSITEVALUEDIALOG_H_ */
