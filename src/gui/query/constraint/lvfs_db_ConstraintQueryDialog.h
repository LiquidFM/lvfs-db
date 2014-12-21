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

#ifndef LVFS_DB_CONSTRAINTQUERYDIALOG_H_
#define LVFS_DB_CONSTRAINTQUERYDIALOG_H_

#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QDialogButtonBox>
#include <lvfs-core/tools/events/KeyboardEventHandler>
#include <lvfs-core/tools/events/KeyboardEventSource>
#include <lvfs-core/tools/events/MouseEventHandler>
#include <lvfs-core/tools/events/MouseEventSource>
#include <lvfs-db/IStorage>
#include "../../../constraints/lvfs_db_BaseConstraint.h"


using namespace ::LVFS;
using namespace ::LVFS::Db;
using namespace ::LVFS::Tools;
using namespace ::LiquidDb;

class ConstraintQueryDialog : public QDialog
{
    Q_OBJECT

public:
    ConstraintQueryDialog(const Interface::Adaptor<IStorage> &container, const Entity::Property &property, QWidget *parent = 0);

    BaseConstraint::Holder takeConstraint(BaseConstraint *parent);
    virtual void accept();

private Q_SLOTS:
    void chooseValue();
    void updateValue(const QString &text);
    void updateValue(const EntityValue &value);
    void updateValue(int index);

private:
    void setEditFont(bool italic);

private:
    typedef KeyboardEventSource<
                EventSourceBase<
                    QLineEdit
                >
            > LineEdit;
    typedef KeyboardEventHandler<
                EventHandlerBase<
                    ConstraintQueryDialog
                >
            > LineEditHandler;

private:
    Interface::Adaptor<IStorage> m_container;
    const Entity::Property &m_property;
    EntityValue m_value;
    LineEditHandler m_handler;
    QLabel m_label;
    QComboBox m_operator;
    LineEdit m_edit;
    QPushButton m_choose;
    QDialogButtonBox m_buttonBox;
    QVBoxLayout m_verticatLayout;
    QHBoxLayout m_horizontalLayout;
};

#endif /* LVFS_DB_CONSTRAINTQUERYDIALOG_H_ */
