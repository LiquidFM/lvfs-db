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

#include "lvfs_db_ValueWidget.h"

#include "lvfs_db_SelectValueWidget.h"
#include "simple/rating/widgets/lvfs_db_RatingValueWidget.h"
#include "simple/widgets/lvfs_db_SimpleValueWidget.h"

#include "../../model/items/lvfs_db_FileItem.h"
#include "../../model/items/lvfs_db_ValueItem.h"
#include "../../model/items/lvfs_db_PropertyItem.h"


#include <liquiddb/EntityValueReader>


template <Entity::Type EntityType>
class NewValueDialog : public SimpleValueWidget<typename EntityValueType<EntityType>::type>
{
public:
    typedef typename EntityValueType<EntityType>::type value_type;
    typedef SimpleValueWidget<value_type>              base_class;

public:
    NewValueDialog(NestedDialog *parent, const QString &title) :
        base_class(parent, title, value_type())
    {}
};


template <Entity::Type EntityType>
inline EntityValue defaultProcessAddValue(NestedDialog *parent, const QString &title, Interface::Adaptor<IStorage> &storage, const Entity &entity, bool &declined)
{
    typedef NewValueDialog<EntityType> NewValueDialog;
    NewValueDialog dialog(parent, title);

    if (dialog.exec() == NewValueDialog::Accepted)
        return storage->addValue(entity, toVariant(dialog.value()));
    else
        declined = true;

    return EntityValue();
}

template <Entity::Type EntityType>
inline EntityValue processAddValue(NestedDialog *parent, const QString &title, Interface::Adaptor<IStorage> &storage, const Entity &entity, bool &declined)
{
    return defaultProcessAddValue<EntityType>(parent, title, storage, entity, declined);
}

template <>
inline EntityValue processAddValue<Entity::Int>(NestedDialog *parent, const QString &title, Interface::Adaptor<IStorage> &storage, const Entity &entity, bool &declined)
{
    if (storage->schema(entity) == IStorage::Rating)
    {
        RatingValueWidget widget(parent, title);

        if (widget.exec() == RatingValueWidget::Accepted)
            return storage->addValue(entity, widget.value());
        else
            declined = true;
    }
    else
        return defaultProcessAddValue<Entity::Int>(parent, title, storage, entity, declined);

    return EntityValue();
}

template <>
inline EntityValue processAddValue<Entity::String>(NestedDialog *parent, const QString &title, Interface::Adaptor<IStorage> &storage, const Entity &entity, bool &declined)
{
    if (storage->schema(entity) == IStorage::Path)
    {
        declined = false;
        return EntityValue();
    }
    else
        return defaultProcessAddValue<Entity::String>(parent, title, storage, entity, declined);

    return EntityValue();
}

template <>
inline EntityValue processAddValue<Entity::Memo>(NestedDialog *parent, const QString &title, Interface::Adaptor<IStorage> &storage, const Entity &entity, bool &declined)
{
    declined = false;
    return EntityValue();
}

template <>
inline EntityValue processAddValue<Entity::Composite>(NestedDialog *parent, const QString &title, Interface::Adaptor<IStorage> &storage, const Entity &entity, bool &declined)
{
    if (storage->transaction())
    {
        EntityValue value(storage->addValue(entity));

        if (value.isValid())
        {
            ValueWidget widget(storage, value, parent, title);

            if (widget.exec() == ValueWidget::Accepted)
                if (storage->commit())
                    return value;
                else
                    storage->rollback();
            else
            {
                declined = true;
                storage->rollback();
            }
        }
    }

    return EntityValue();
}


ValueWidgetPrivate::ICallback::~ICallback()
{}

ValueWidgetPrivate::ValueWidgetPrivate(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, ICallback *callback, EventHandler *handler) :
    QWidget(),
    m_storage(storage),
    m_value(value),
    m_entity(m_value.entity()),
    m_callback(callback),
    m_vLayout(this),
    m_handler(this),
    m_filter(&m_handler, this),
    m_search(QIcon(), QString(), this),
    m_view(handler, this),
    m_delegate(m_storage, m_entity),
    m_model(m_storage, m_value)
{
    init();
}

ValueWidgetPrivate::ValueWidgetPrivate(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, ICallback *callback, EventHandler *handler) :
    QWidget(),
    m_storage(storage),
    m_value(),
    m_entity(reader.entity()),
    m_callback(callback),
    m_vLayout(this),
    m_handler(this),
    m_filter(&m_handler, this),
    m_search(QIcon(), QString(), this),
    m_view(handler, this),
    m_delegate(m_storage, m_entity),
    m_model(m_storage, reader)
{
    init();
}

ValueWidgetPrivate::ValueWidgetPrivate(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, ICallback *callback, EventHandler *handler) :
    QWidget(),
    m_storage(storage),
    m_value(value),
    m_entity(m_value.entity()),
    m_callback(callback),
    m_vLayout(this),
    m_handler(this),
    m_filter(&m_handler, this),
    m_search(QIcon(), QString(), this),
    m_view(handler, this),
    m_delegate(m_storage, m_entity),
    m_model(m_storage, m_value, files)
{
    init();
}

void ValueWidgetPrivate::edit()
{
    m_view.edit(m_view.selectionModel()->currentIndex());
}

bool ValueWidgetPrivate::dblClick()
{
    QModelIndex index = currentIndex();

    if (index.isValid())
    {
        Item *item = static_cast<Item *>(index.internalPointer());

        if (item->isPath())
        {
            static_cast<FileItem *>(item)->open();
            return true;
        }
    }

    return false;
}

void ValueWidgetPrivate::addValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid())
    {
        Item *item = static_cast<Item *>(index.internalPointer());

        if (item->isProperty())
            doAddValue(static_cast<PropertyItem *>(item));
        else
            if (item->parent() == NULL)
                doAddValue();
            else
            {
                do
                {
                    item = item->parent();
                    ASSERT(item != NULL);
                }
                while (!item->isProperty());

                doAddValue(static_cast<PropertyItem *>(item));
            }
    }
    else
        doAddValue();
}

void ValueWidgetPrivate::removeValue()
{
    QModelIndex index = currentIndex();

    if (index.isValid())
    {
        Item *item = static_cast<Item *>(index.internalPointer());

        if (item->isValue())
            if (item->parent())
                if (item->parent()->isProperty())
                {
                    EntityValue value(static_cast<ValueItem *>(item)->value());
                    const EntityValue &parentValue = item->parent()->parent() ? static_cast<ValueItem *>(item->parent()->parent())->value() : m_value;

                    if (m_storage->removeValue(parentValue, value))
                        m_model.remove(index);
                    else
                        m_callback->critical(toUnicode(m_storage->lastError()));
                }
                else
                    m_model.remove(index);
            else
            {
                Entity::IdsList list;
                list.push_back(static_cast<ValueItem *>(item)->value().id());

                if (m_storage->removeValue(m_entity, list))
                    m_model.remove(index);
                else
                    m_callback->critical(toUnicode(m_storage->lastError()));
            }
    }
}

void ValueWidgetPrivate::setFocusToFilter()
{
    m_filter.setFocus();
    m_filter.selectAll();
}

void ValueWidgetPrivate::selectPathProperty()
{
    QModelIndex index = currentIndex();

    if (!index.isValid())
        return;
    else
        index = m_model.pathPropertyIndex(index);

    if (!index.isValid())
        return;
    else
        index = m_proxy.mapFromSource(index);

    m_view.setFocus();
    m_view.scrollTo(index, QAbstractItemView::PositionAtCenter);
    m_view.selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Columns);
    m_view.selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
    m_view.expand(index);
}

void ValueWidgetPrivate::doAddValue()
{
    bool declined = false;
    QString title = tr("New value for \"%1\"").arg(toUnicode(m_entity.name()));
    EntityValue value;

    switch (m_entity.type())
    {
        case Entity::Int:
            value = processAddValue<Entity::Int>(m_callback->parent(), title, m_storage, m_entity, declined);
            break;

        case Entity::String:
            value = processAddValue<Entity::String>(m_callback->parent(), title, m_storage, m_entity, declined);
            break;

        case Entity::Date:
            value = processAddValue<Entity::Date>(m_callback->parent(), title, m_storage, m_entity, declined);
            break;

        case Entity::Time:
            value = processAddValue<Entity::Time>(m_callback->parent(), title, m_storage, m_entity, declined);
            break;

        case Entity::DateTime:
            value = processAddValue<Entity::DateTime>(m_callback->parent(), title, m_storage, m_entity, declined);
            break;

        case Entity::Memo:
            value = processAddValue<Entity::Memo>(m_callback->parent(), title, m_storage, m_entity, declined);
            break;

        case Entity::Composite:
            value = processAddValue<Entity::Composite>(m_callback->parent(), title, m_storage, m_entity, declined);
            break;

//        case Entity::Rating:
//            value = processAddValue<Entity::Rating>(m_callback->parent(), title, m_storage, entity, declined);
//            break;
//
//        case Entity::Path:
//            value = processAddValue<Entity::Path>(m_callback->parent(), title, m_storage, entity, declined);
//            break;

        default:
            break;
    }

    if (value.isValid())
    {
        setCurrentIndex(m_model.add(value));
        m_callback->acceptAndClose();
    }
    else
        if (!declined)
            m_callback->critical(toUnicode(m_storage->lastError()));
}

void ValueWidgetPrivate::doAddValue(PropertyItem *item)
{
    if (m_storage->transaction())
    {
        EntityValueReader reader(m_storage->entityValues(item->entity()));
        SelectValueWidget dialog(m_storage, reader, m_callback->parent());

        if (dialog.exec() == SelectValueWidget::Accepted)
        {
            EntityValue value;
            const EntityValue &parentValue = item->parent() ? static_cast<ValueItem *>(item->parent())->value() : m_value;

            if (m_storage->addValue(parentValue, value = dialog.value()))
                if (m_storage->commit())
                    setCurrentIndex(m_model.add(item, value));
                else
                {
                    m_storage->rollback();
                    m_callback->critical(toUnicode(m_storage->lastError()));
                }
            else
            {
                m_storage->rollback();
                m_callback->critical(toUnicode(m_storage->lastError()));
            }
        }
        else
            m_storage->rollback();
    }
    else
        m_callback->critical(toUnicode(m_storage->lastError()));
}

void ValueWidgetPrivate::setFilter()
{
    m_proxy.setFilter(m_filter.text());

    if (!m_filter.text().isEmpty())
    {
        m_view.setFocus();

        if (m_model.canFetchMore(QModelIndex()))
            m_model.fetchMore(QModelIndex());
    }
}

void ValueWidgetPrivate::clearFilter()
{
    if (m_filter.text().isEmpty())
        m_view.setFocus();
    else
        m_filter.clear();

    m_proxy.setFilter(QString());
}

void ValueWidgetPrivate::selectValue(const QModelIndex &index)
{
    Item *item = static_cast<Item *>(m_proxy.mapToSource(index).internalPointer());

    if (item->parent() == NULL && item->isValue())
        m_filter.setText(toUnicode(static_cast<ValueItem *>(item)->value().value().asString()));
}

void ValueWidgetPrivate::setCurrentIndex(const QModelIndex &index)
{
    m_filter.setText(QString());
    setFilter();
    m_view.selectionModel()->setCurrentIndex(m_proxy.mapFromSource(index), QItemSelectionModel::ClearAndSelect);
}

void ValueWidgetPrivate::init()
{
    m_vLayout.setMargin(1);
    m_vLayout.setSpacing(1);

    m_hLayout.setMargin(1);
    m_hLayout.setSpacing(1);
    m_hLayout.addWidget(&m_filter);
    m_hLayout.addWidget(&m_search);

    m_view.setHeaderHidden(true);

    m_vLayout.addLayout(&m_hLayout);
    m_vLayout.addWidget(&m_view);

    m_proxy.setDynamicSortFilter(true);
    m_proxy.setSourceModel(&m_model);
    m_view.setSortingEnabled(true);
    m_view.sortByColumn(0, Qt::AscendingOrder);
    m_view.setModel(&m_proxy);
    m_view.setItemDelegate(&m_delegate);

    connect(&m_search, SIGNAL(clicked()), this, SLOT(setFilter()));
    connect(&m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(selectValue(QModelIndex)));

    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Enter, &ValueWidgetPrivate::setFilter);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Return, &ValueWidgetPrivate::setFilter);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Escape, &ValueWidgetPrivate::clearFilter);
    m_filter.setToolTip(tr("ENTER - accept filter\nESC - clear filter, if filter is empty move focus to view"));

    m_search.setToolTip(tr("Accept filter"));
}

MainValueWidget::MainValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, EventHandler *handler, NestedDialog *parent) :
    BaseNestedWidget(parent),
    m_private(storage, value, this, handler)
{}

MainValueWidget::MainValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, EventHandler *handler, NestedDialog *parent) :
    BaseNestedWidget(parent),
    m_private(storage, reader, this, handler)
{}

MainValueWidget::MainValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, EventHandler *handler, NestedDialog *parent) :
    BaseNestedWidget(parent),
    m_private(storage, value, files, this, handler)
{}

QWidget *MainValueWidget::centralWidget()
{
    return &m_private;
}

void MainValueWidget::setReadOnly(bool value)
{
    m_private.view().setEnabled(!value);
}

void MainValueWidget::setFocus()
{
    m_private.view().setFocus();
}

void MainValueWidget::acceptAndClose()
{
    accept();
}

NestedDialog *MainValueWidget::parent()
{
    return BaseNestedWidget::parent();
}

void MainValueWidget::critical(const QString &text)
{
    BaseNestedWidget::critical(text);
}

ValueWidget::ValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, NestedDialog *parent, const QString &title) :
    NestedWidget(parent, title),
    m_handler(this),
    m_private(storage, value, this, &m_handler)
{
    init();
}

ValueWidget::ValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, NestedDialog *parent, const QString &title) :
    NestedWidget(parent, title),
    m_handler(this),
    m_private(storage, reader, this, &m_handler)
{
    init();
}

ValueWidget::ValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, NestedDialog *parent, const QString &title) :
    NestedWidget(parent, title),
    m_handler(this),
    m_private(storage, value, files, this, &m_handler)
{
    init();
}

void ValueWidget::setFocus()
{
    m_private.view().setFocus();
}

void ValueWidget::acceptAndClose()
{
    accept();
}

NestedDialog *ValueWidget::parent()
{
    return BaseNestedWidget::parent();
}

void ValueWidget::critical(const QString &text)
{
    BaseNestedWidget::critical(text);
}

void ValueWidget::edit()
{
    m_private.edit();
}

bool ValueWidget::dblClick()
{
    return m_private.dblClick();
}

void ValueWidget::addValue()
{
    m_private.addValue();
}

void ValueWidget::removeValue()
{
    m_private.removeValue();
}

void ValueWidget::setFocusToFilter()
{
    m_private.setFocusToFilter();
}

void ValueWidget::enterPressed()
{
    if (!m_private.dblClick())
        m_private.selectPathProperty();
}

void ValueWidget::init()
{
    m_handler.registerMouseDoubleClickEventHandler(&ValueWidget::dblClick);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_F2,     &ValueWidget::edit);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Insert, &ValueWidget::addValue);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Delete, &ValueWidget::removeValue);
    m_handler.registerShortcut(Qt::CTRL,       Qt::Key_F,      &ValueWidget::setFocusToFilter);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Return, &ValueWidget::enterPressed);
    m_handler.registerShortcut(Qt::NoModifier, Qt::Key_Enter,  &ValueWidget::enterPressed);
    m_handler.registerShortcut(Qt::CTRL,       Qt::Key_Return, &ValueWidget::accept);
    m_handler.registerShortcut(Qt::CTRL,       Qt::Key_Enter,  &ValueWidget::accept);

    m_private.view().setToolTip(tr("INS - add value\nDEL - remove value\nCTRL+F - activate filter field"));
    setCentralWidget(&m_private);
}
