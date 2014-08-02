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

#include "lvfs_db_CreateEntityDialog.h"
#include "../../lvfs_db_common.h"

#include <liquiddb/EntityTitle>
#include <lvfs-core/models/Qt/SortFilterModel>
#include <lvfs-core/tools/widgets/StringDialog>
#include <QtGui/QMessageBox>


CreateEntityDialog::CreateEntityDialog(const Interface::Adaptor<IStorage> &container, const QString &name, QWidget *parent) :
    QDialog(parent),
    m_label(this),
    m_lineEdit(name, this),
    m_label2(this),
    m_lineEdit2(this),
    m_label3(this),
    m_comboBox(this),
    m_view(this),
    m_addEntity(tr("Add"), this),
    m_removeEntity(tr("Remove"), this),
    m_gridLayout(this),
    m_buttonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, Qt::Horizontal, this),
    m_model(this),
    m_delegate(container)
{
    setWindowTitle(tr("Create a new entity"));
    setListEnabled(false);

    QFont font;
    font.setBold(true);
    font.setWeight(75);
    m_label.setFont(font);
    m_label.setText(tr("Name"));
    m_label2.setFont(font);
    m_label2.setText(tr("Short format"));
    m_label3.setFont(font);
    m_label3.setText(tr("Type"));

    m_gridLayout.setMargin(3);
    m_gridLayout.setSpacing(1);
    m_gridLayout.addWidget(&m_label,       0, 0, 1, 1);
    m_gridLayout.addWidget(&m_lineEdit,    0, 1, 1, 1);
    m_gridLayout.addWidget(&m_label3,      1, 0, 1, 1);
    m_gridLayout.addWidget(&m_comboBox,    1, 1, 1, 1);
    m_gridLayout.addWidget(&m_label2,      2, 0, 1, 1);
    m_gridLayout.addWidget(&m_lineEdit2,   2, 1, 1, 1);
    m_gridLayout.addLayout(&m_gridLayout2, 3, 0, 1, 2);
    m_gridLayout.addWidget(&m_buttonBox,   4, 0, 1, 2);

    m_horizontalLayout.setMargin(3);
    m_horizontalLayout.setSpacing(1);
    m_horizontalLayout.addWidget(&m_addEntity);
    m_horizontalLayout.addWidget(&m_removeEntity);

    m_gridLayout2.setMargin(3);
    m_gridLayout2.setSpacing(1);
    m_gridLayout2.addLayout(&m_horizontalLayout, 0, 0, 1, 1);
    m_gridLayout2.addWidget(&m_view, 1, 0, 1, 1);

    connect(&m_addEntity, SIGNAL(clicked()), this, SLOT(add()));
    connect(&m_removeEntity, SIGNAL(clicked()), this, SLOT(remove()));

    m_view.setHeaderHidden(true);
    m_view.setModel(&m_model);
    m_view.setItemDelegate(&m_delegate);

    connect(&m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(&m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    m_lineEdit.selectAll();

    for (auto &i : EntityTypes::instance())
        m_comboBox.addItem(i.second.label, i.first);

    m_comboBox.setCurrentIndex(0);
    connect(&m_comboBox, SIGNAL(activated(int)), this, SLOT(activated(int)));
}

void CreateEntityDialog::accept()
{
    if (name().empty())
        QMessageBox::warning(this, windowTitle(), tr("You must enter the name!"));
    else
    {
        if (m_lineEdit2.isEnabled())
        {
            EntityTitle title(CreateEntityDialog::title());

            if (title.isValid())
            {
                bool ok;

                for (auto i : title)
                    if (i.type() == EntityTitle::Token::Property)
                    {
                        ok = false;

                        for (size_type q = 0, size = m_model.size(); q < size; ++q)
                            if (m_model.nameAt(q) == i.string())
                            {
                                ok = true;
                                break;
                            }

                        if (!ok)
                        {
                            QMessageBox::warning(
                                    this,
                                    windowTitle(),
                                    tr("Short format points to property \"%1\" which is not in properties of this entity!").
                                        arg(toUnicode(i.string())));
                            return;
                        }
                    }
            }
            else
            {
                QMessageBox::warning(this, windowTitle(), tr("Short format is invalid (%1)!"));
                return;
            }
        }

        for (size_type i = 0, q, size = m_model.size(); i < size; ++i)
            for (q = i + 1; q < size; ++q)
                if (m_model.entityAt(q).id() == m_model.entityAt(i).id())
                {
                    QMessageBox::warning(this, windowTitle(), tr("More than one property of type \"%1\"!").arg(toUnicode(m_model.entityAt(i).name())));
                    return;
                }
                else
                    if (Core::Qt::SortFilterModel::compareFileNames(m_model.nameAt(q).c_str(), m_model.nameAt(i).c_str()) == 0)
                    {
                        QMessageBox::warning(this, windowTitle(), tr("There is a properties with the same names \"%1\"!").arg(toUnicode(m_model.nameAt(i))));
                        return;
                    }

        QDialog::accept();
    }
}

void CreateEntityDialog::activated(int index)
{
    setListEnabled(m_comboBox.itemData(index, Qt::UserRole).toInt() == Entity::Composite);
}

void CreateEntityDialog::add()
{
    if (m_delegate.container()->entities().size() == 0)
        QMessageBox::warning(this, windowTitle(), tr("There is no entities!"));
    else
    {
        StringDialog dialog(tr("New property name"), tr("Name"), QString(), this);

        if (dialog.exec() == StringDialog::Accepted)
            m_model.add((*m_delegate.container()->entities().begin()).second, fromUnicode(dialog.value()).data());
    }
}

void CreateEntityDialog::remove()
{
    QModelIndex index = m_view.currentIndex();

    if (index.isValid())
        m_model.remove(index);
}

void CreateEntityDialog::setListEnabled(bool enabled)
{
    m_view.setEnabled(enabled);
    m_addEntity.setEnabled(enabled);
    m_removeEntity.setEnabled(enabled);
    m_label2.setEnabled(enabled);
    m_lineEdit2.setEnabled(enabled);
}
