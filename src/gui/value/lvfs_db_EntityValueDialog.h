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

#ifndef LVFS_DB_VALUEDIALOG_H_
#define LVFS_DB_VALUEDIALOG_H_

#include <lvfs-core/tools/widgets/NestedPlainDialog>
#include "lvfs_db_ValueWidget.h"


class PLATFORM_MAKE_PRIVATE EntityValueDialog : public NestedPlainDialog
{
    Q_OBJECT

public:
    EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, QWidget *parent = 0);
    EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, QWidget *parent = 0);

protected:
    virtual void addValue();
    virtual void removeValue();

protected:
    QModelIndex currentIndex() const { return m_mainWidget.currentIndex(); }

    const Interface::Adaptor<IStorage> &storage() const { return m_mainWidget.storage(); }
    Interface::Adaptor<IStorage> &storage() { return m_mainWidget.storage(); }

    const ValueModel &model() const { return m_mainWidget.model(); }
    ValueModel &model() { return m_mainWidget.model(); }

    void doAddValue() { m_mainWidget.addValue(); }
    void doRemoveValue() { m_mainWidget.removeValue(); }
    void doEdit() { m_mainWidget.edit(); }

private:
    void openFile1();
    void openFile2();
    void edit();

private:
    typedef MouseDoubleClickEventHandler<
                KeyboardEventHandler<
                    EventHandlerBase<
                        EntityValueDialog
                    >
                >
            > TreeViewHandler;

private:
    TreeViewHandler m_handler;
    MainValueWidget m_mainWidget;
};

#endif /* LVFS_DB_VALUEDIALOG_H_ */
