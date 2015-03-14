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

#ifndef LVFS_DB_VALUEWIDGET_H_
#define LVFS_DB_VALUEWIDGET_H_

#include <QtGui/QTreeView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtCore/QCoreApplication>
#include <lvfs-core/tools/events/KeyboardEventHandler>
#include <lvfs-core/tools/events/KeyboardEventSource>
#include <lvfs-core/tools/events/MouseEventHandler>
#include <lvfs-core/tools/events/MouseEventSource>
#include <lvfs-core/tools/widgets/NestedWidget>
#include "../../model/lvfs_db_ValueModel.h"
#include "../../model/lvfs_db_ValueDelegate.h"
#include "../../model/lvfs_db_FilterValueModel.h"


namespace LVFS {
namespace Db {

class Item;
class PropertyItem;

}}

using namespace ::LVFS;
using namespace ::LVFS::Db;
using namespace ::LVFS::Tools;

class PLATFORM_MAKE_PRIVATE ValueWidgetPrivate : public QWidget
{
    Q_OBJECT

public:
    class ICallback
    {
    public:
        virtual ~ICallback();

        virtual void acceptAndClose() = 0;
        virtual NestedDialog *parent() = 0;
        virtual void critical(const QString &text) = 0;
    };

    typedef MouseDoubleClickEventSource<
                KeyboardEventSource<
                    EventSourceBase<
                        QTreeView
                    >
                >
            > TreeView;

    typedef KeyboardEventSource<
                EventSourceBase<
                    QLineEdit
                >
            > LineEdit;

    typedef KeyboardEventHandler<
                EventHandlerBase<
                    ValueWidgetPrivate
                >
            > LineEditHandler;

public:
    ValueWidgetPrivate(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, ICallback *callback, EventHandler *handler);
    ValueWidgetPrivate(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, ICallback *callback, EventHandler *handler);
    ValueWidgetPrivate(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, ICallback *callback, EventHandler *handler);

    const Interface::Adaptor<IStorage> &storage() const { return m_storage; }
    Interface::Adaptor<IStorage> &storage() { return m_storage; }

    const Entity &entity() const { return m_entity; }

    const TreeView &view() const { return m_view; }
    TreeView &view() { return m_view; }

    const FilterValueModel &proxy() const { return m_proxy; }
    FilterValueModel &proxy() { return m_proxy; }

    const ValueModel &model() const { return m_model; }
    ValueModel &model() { return m_model; }

    QModelIndex currentIndex() const { return m_proxy.mapToSource(m_view.selectionModel()->currentIndex()); }
    void setCurrentIndex(Item *item);

    void edit() { m_view.edit(currentIndex()); }
    void addValue();
    void removeValue();
    void setFocusToFilter() { m_filter.setFocus(); }

private:
    void doAddValue();
    void doAddValue(PropertyItem *item);

private Q_SLOTS:
    void setFilter();
    void clearFilter();
    void selectValue(const QModelIndex &index);

private:
    void setCurrentIndex(const QModelIndex &index) const;

private:
    void init();

private:
    Interface::Adaptor<IStorage> m_storage;
    EntityValue m_value;
    Entity m_entity;

private:
    ICallback *m_callback;

    QVBoxLayout m_vLayout;
    QHBoxLayout m_hLayout;

    LineEditHandler m_handler;
    LineEdit m_filter;
    QPushButton m_search;

    TreeView m_view;
    ValueDelegate m_delegate;
    ValueModel m_model;
    FilterValueModel m_proxy;
};


class PLATFORM_MAKE_PRIVATE MainValueWidget : public BaseNestedWidget, public ValueWidgetPrivate::ICallback
{
public:
    MainValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, EventHandler *handler, NestedDialog *parent);
    MainValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, EventHandler *handler, NestedDialog *parent);
    MainValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, EventHandler *handler, NestedDialog *parent);

    /* BaseNestedWidget */
    virtual QWidget *centralWidget();
    virtual void setReadOnly(bool value);
    virtual void setFocus();

    /* ValueWidgetPrivate::ICallback */
    virtual void acceptAndClose();
    virtual NestedDialog *parent();
    virtual void critical(const QString &text);

    const Interface::Adaptor<IStorage> &storage() const { return m_private.storage(); }
    Interface::Adaptor<IStorage> &storage() { return m_private.storage(); }

    const Entity &entity() const { return m_private.entity(); }

    const ValueModel &model() const { return m_private.model(); }
    ValueModel &model() { return m_private.model(); }

    QModelIndex currentIndex() const { return m_private.currentIndex(); }
    void setCurrentIndex(Item *item) { m_private.setCurrentIndex(item); }

    EntityValue takeValue() { return m_private.model().take(currentIndex()); }

    void edit() { m_private.edit(); }
    void addValue() { m_private.addValue(); }
    void removeValue() { m_private.removeValue(); }
    void setFocusToFilter() { m_private.setFocusToFilter(); }
    void setViewToolTip(const QString &value) { m_private.view().setToolTip(value); }

private:
    ValueWidgetPrivate m_private;
};


class PLATFORM_MAKE_PRIVATE ValueWidget : public NestedWidget, public ValueWidgetPrivate::ICallback
{
public:
    ValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, NestedDialog *parent, const QString &title);
    ValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, NestedDialog *parent, const QString &title);
    ValueWidget(const Interface::Adaptor<IStorage> &storage, const EntityValue &value, const ValueModel::Files &files, NestedDialog *parent, const QString &title);

    /* BaseNestedWidget */
    virtual void setFocus();

    /* ValueWidgetPrivate::ICallback */
    virtual void acceptAndClose();
    virtual NestedDialog *parent();
    virtual void critical(const QString &text);

    const Interface::Adaptor<IStorage> &storage() const { return m_private.storage(); }
    Interface::Adaptor<IStorage> &storage() { return m_private.storage(); }

    const ValueModel &model() const { return m_private.model(); }
    ValueModel &model() { return m_private.model(); }

    QModelIndex currentIndex() const { return m_private.currentIndex(); }

    EntityValue takeValue() { return m_private.model().take(currentIndex()); }

    void addValue();
    void removeValue();
    void setFocusToFilter();

private:
    void init();

private:
    typedef KeyboardEventHandler<
                EventHandlerBase<
                    ValueWidget
                >
            > TreeViewHandler;

private:
    TreeViewHandler m_handler;
    ValueWidgetPrivate m_private;
};

#endif /* LVFS_DB_VALUEWIDGET_H_ */
