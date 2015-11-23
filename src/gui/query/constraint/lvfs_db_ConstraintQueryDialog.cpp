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

#include "lvfs_db_ConstraintQueryDialog.h"
#include "../../value/lvfs_db_SelectValueDialog.h"
#include "../../../constraints/value/lvfs_db_ValueConstraint.h"
#include "../../../lvfs_db_common.h"

#include <QtGui/QMessageBox>


ConstraintQueryDialog::ConstraintQueryDialog(const Interface::Adaptor<IStorage> &container, const Entity::Property &property, QWidget *parent) :
    QDialog(parent),
    m_container(container),
    m_property(property),
    m_value(),
    m_handler(this),
    m_label(toUnicode(m_property.name), this),
    m_operator(this),
    m_edit(&m_handler, this),
    m_choose(QIcon(), QString(), this),
    m_buttonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, Qt::Horizontal, this),
    m_verticatLayout(this)
{
    setWindowTitle(tr("Constraint on \"%1\" property").arg(toUnicode(m_property.name)));

    m_horizontalLayout.setMargin(3);
    m_horizontalLayout.setSpacing(1);
    m_horizontalLayout.addWidget(&m_label);
    m_horizontalLayout.addWidget(&m_operator);
    m_horizontalLayout.addWidget(&m_edit, 1);
    m_horizontalLayout.addWidget(&m_choose);

    connect(&m_choose, SIGNAL(clicked()), this, SLOT(chooseValue()));
    connect(&m_edit, SIGNAL(textEdited(QString)), this, SLOT(updateValue(QString)));
    connect(&m_operator, SIGNAL(currentIndexChanged(int)), this, SLOT(updateValue(int)));

    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Insert, &ConstraintQueryDialog::chooseValue);
    m_edit.setToolTip(tr("INS - choose a value"));

    m_verticatLayout.setMargin(3);
    m_verticatLayout.setSpacing(1);
    m_verticatLayout.addLayout(&m_horizontalLayout);
    m_verticatLayout.addWidget(&m_buttonBox);

    connect(&m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(&m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    switch (m_property.entity.type())
    {
        case Entity::Int:
        case Entity::Date:
        case Entity::Time:
        case Entity::DateTime:
        {
            for (int op = Constraint::Less; op < Constraint::Like; ++op)
                m_operator.addItem(toUnicode(Constraint::operatorToString(static_cast<Constraint::Operator>(op))), op);

            break;
        }

        case Entity::String:
        case Entity::Memo:
        {
            m_operator.addItem(toUnicode(Constraint::operatorToString(Constraint::Like)), Constraint::Like);
            m_operator.addItem(toUnicode(Constraint::operatorToString(Constraint::Equal)), Constraint::Equal);

            break;
        }

        case Entity::Composite:
        {
            m_operator.addItem(toUnicode(Constraint::operatorToString(Constraint::Equal)), Constraint::Equal);
            m_edit.setReadOnly(true);

            break;
        }

        default:
            break;
    }

    m_operator.setCurrentIndex(0);
    m_edit.setFocus();
}

BaseConstraint::Holder ConstraintQueryDialog::takeConstraint(BaseConstraint *parent)
{
    if (m_value.isValid())
        return BaseConstraint::Holder(new ValueConstraint(
                m_property,
                static_cast<Constraint::Operator>(m_operator.itemData(m_operator.currentIndex(), Qt::UserRole).toInt()),
                m_value,
                parent));
    else
        return BaseConstraint::Holder(new ValueConstraint(
                m_property,
                static_cast<Constraint::Operator>(m_operator.itemData(m_operator.currentIndex(), Qt::UserRole).toInt()),
                EntityValue::createSimpleValue(m_property.entity, EntityValue::InvalidId, fromUnicode(m_edit.text()).data()),
                parent));
}

void ConstraintQueryDialog::accept()
{
    if (m_edit.text().isEmpty())
        QMessageBox::warning(this, windowTitle(), tr("You must enter or select a value."));
    else
        QDialog::accept();
}

void ConstraintQueryDialog::chooseValue()
{
    EntityValueReader reader(m_container->entityValues(m_property.entity));
    SelectValueDialog dialog(m_container, reader, this);

    if (dialog.exec() == SelectValueDialog::Accepted)
    {
        updateValue(dialog.value());
        m_buttonBox.setFocus();
    }
    else
        m_edit.setFocus();
}

void ConstraintQueryDialog::updateValue(const QString &text)
{
    setEditFont(false);
    m_value = EntityValue();
}

void ConstraintQueryDialog::updateValue(const EntityValue &value)
{
    if (m_operator.itemData(m_operator.currentIndex(), Qt::UserRole).toInt() == Constraint::Equal)
        m_value = EntityValue();
    else
        for (int i = 0, size = m_operator.count(); i < size; ++i)
            if (m_operator.itemData(i, Qt::UserRole).toInt() == Constraint::Equal)
            {
                m_operator.setCurrentIndex(i);
                break;
            }

    setEditFont(true);
    m_edit.setText(toUnicode((m_value = value).value().asString()));
}

void ConstraintQueryDialog::updateValue(int index)
{
    setEditFont(false);
    m_value = EntityValue();
}

void ConstraintQueryDialog::setEditFont(bool italic)
{
    if (m_edit.font().italic() != italic)
    {
        QFont font(m_edit.font());

        font.setItalic(italic);
        m_edit.setFont(font);
    }
}
