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

#ifndef LVFS_DB_CHOOSEENTITYDIALOG_H_
#define LVFS_DB_CHOOSEENTITYDIALOG_H_

#include <QtCore/QList>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QDialogButtonBox>
#include <lvfs-db/IStorage>


using namespace ::LVFS;
using namespace ::LVFS::Db;

class PLATFORM_MAKE_PRIVATE ChooseEntityDialog : public QDialog
{
    Q_OBJECT

public:
    const Entity &value() const { return (*m_container->entities().find(m_comboBox.itemData(m_comboBox.currentIndex()).toLongLong())).second; }
    static Entity chooseFile(const Interface::Adaptor<IStorage> &container, QWidget *parent = 0);
    static Entity chooseProperty(const Interface::Adaptor<IStorage> &container, const Entity &entity, ::EFC::String &propertyName, QWidget *parent = 0);

protected:
    ChooseEntityDialog(const QString &title, const Interface::Adaptor<IStorage> &container, const LiquidDb::Storage::Entities &entities, QWidget *parent = 0);

protected:
    const Interface::Adaptor<IStorage> &m_container;
    QVBoxLayout m_verticatLayout;

private:
    QLabel m_label;
    QComboBox m_comboBox;
    QDialogButtonBox m_buttonBox;
    QHBoxLayout m_horizontalLayout;
};

#endif /* LVFS_DB_CHOOSEENTITYDIALOG_H_ */
