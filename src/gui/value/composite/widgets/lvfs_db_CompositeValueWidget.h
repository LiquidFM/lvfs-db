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

#ifndef LVFS_DB_COMPOSITEVALUEWIDGET_H_
#define LVFS_DB_COMPOSITEVALUEWIDGET_H_

#include <QtGui/QTreeView>
#include <lvfs-core/tools/events/KeyboardEventHandler>
#include <lvfs-core/tools/events/KeyboardEventSource>
#include <lvfs-core/tools/events/MouseEventHandler>
#include <lvfs-core/tools/events/MouseEventSource>
#include <lvfs-core/tools/widgets/NestedWidget>
#include "../../model/lvfs_db_CompositeValueModel.h"
#include "../../model/lvfs_db_CompositeValueDelegate.h"


using namespace ::LVFS;
using namespace ::LVFS::Db;
using namespace ::LVFS::Tools;

class CompositeValueWidgetPrivate
{
public:
    class ICallback
    {
    public:
        virtual ~ICallback();

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

public:
    CompositeValueWidgetPrivate(ICallback *callback, EventHandler *handler, const Interface::Adaptor<IStorage> &container, const EntityValue &value);
//    CompositeValueWidgetPrivate(ICallback *callback, EventHandler *handler, const Interface::Adaptor<IStorage> &container, const EntityValue &value, const CompositeValueModel::Files &files);

    const Interface::Adaptor<IStorage> &container() const { return m_container; }
    Interface::Adaptor<IStorage> &container() { return m_container; }

    const TreeView &view() const { return m_view; }
    TreeView &view() { return m_view; }

    const CompositeValueModel &model() const { return m_model; }
    CompositeValueModel &model() { return m_model; }

    void open(const QModelIndex &index);
    void addValue(const QModelIndex &index);
    void removeValue(const QModelIndex &index);

private:
    ICallback *m_callback;
    Interface::Adaptor<IStorage> m_container;
    EntityValue m_value;
    TreeView m_view;
    CompositeValueModel m_model;
    CompositeValueDelegate m_delegate;
};


class MainCompositeValueWidget : public BaseNestedWidget, public CompositeValueWidgetPrivate::ICallback
{
public:
    MainCompositeValueWidget(EventHandler *handler, const Interface::Adaptor<IStorage> &container, const EntityValue &value, NestedDialog *parent);
//    MainCompositeValueWidget(EventHandler *handler, const Interface::Adaptor<IStorage> &container, const EntityValue &value, const CompositeValueModel::Files &files, NestedDialog *parent);

    /* BaseNestedWidget */
    virtual QWidget *centralWidget();
    virtual void setReadOnly(bool value);
    virtual void setFocus();

    /* CompositeValueWidgetPrivate::ICallback */
    virtual NestedDialog *parent();
    virtual void critical(const QString &text);

    QModelIndex currentIndex() const { return m_private.view().selectionModel()->currentIndex(); }

    const Interface::Adaptor<IStorage> &container() const { return m_private.container(); }
    Interface::Adaptor<IStorage> &container() { return m_private.container(); }

    const CompositeValueModel &model() const { return m_private.model(); }
    CompositeValueModel &model() { return m_private.model(); }

    void open(const QModelIndex &index) { m_private.open(index); }
    void edit(const QModelIndex &index) { m_private.view().edit(index); }
    void addValue(const QModelIndex &index) { m_private.addValue(index); }
    void removeValue(const QModelIndex &index) { m_private.removeValue(index); }
    void setViewToolTip(const QString &value) { m_private.view().setToolTip(value); }

private:
    CompositeValueWidgetPrivate m_private;
};


class CompositeValueWidget : public NestedWidget, public CompositeValueWidgetPrivate::ICallback
{
public:
    CompositeValueWidget(const Interface::Adaptor<IStorage> &container, const EntityValue &value, NestedDialog *parent, const QString &title);

    /* BaseNestedWidget */
    virtual void setFocus();

    /* CompositeValueWidgetPrivate::ICallback */
    virtual NestedDialog *parent();
    virtual void critical(const QString &text);

    QModelIndex currentIndex() const { return m_private.view().selectionModel()->currentIndex(); }

    const Interface::Adaptor<IStorage> &container() const { return m_private.container(); }
    Interface::Adaptor<IStorage> &container() { return m_private.container(); }

    const CompositeValueModel &model() const { return m_private.model(); }
    CompositeValueModel &model() { return m_private.model(); }

    void addValue();
    void removeValue();

private:
    typedef KeyboardEventHandler<
                EventHandlerBase<
                    CompositeValueWidget
                >
            > TreeViewHandler;

private:
    TreeViewHandler m_handler;
    CompositeValueWidgetPrivate m_private;
};

#endif /* LVFS_DB_COMPOSITEVALUEWIDGET_H_ */
