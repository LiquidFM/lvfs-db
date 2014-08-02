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

#ifndef LVFS_DB_EDITABLEVALUELISTDIALOG_H_
#define LVFS_DB_EDITABLEVALUELISTDIALOG_H_

#include <lvfs-core/tools/widgets/NestedPlainDialog>
#include "widgets/lvfs_db_EditableValueListWidget.h"


class EditableValueListDialog : public NestedPlainDialog
{
    Q_OBJECT

public:
    EditableValueListDialog(const Interface::Adaptor<IStorage> &container, const EntityValueReader &reader, QWidget *parent = 0);
    virtual ~EditableValueListDialog();

    virtual void accept();
    virtual void reject();

protected:
    void closeDbContext();
    EntityValue takeValue();
    QModelIndex currentIndex() const;

private:
    typedef MouseDoubleClickEventHandler<
                KeyboardEventHandler<
                    EventHandlerBase<
                        EditableValueListDialog
                    >
                >
            > TreeViewHandler;

    void addValue();
    void removeValue();
    void setFocusToFilter();

private:
    TreeViewHandler m_handler;
    MainEditableValueListWidget m_widget;
};

#endif /* LVFS_DB_EDITABLEVALUELISTDIALOG_H_ */
