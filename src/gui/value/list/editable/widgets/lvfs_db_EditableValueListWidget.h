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

#ifndef LVFS_DB_EDITABLEVALUELISTWIDGET_H_
#define LVFS_DB_EDITABLEVALUELISTWIDGET_H_

#include <QtGui/QTreeView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtCore/QCoreApplication>
#include <lvfs-db/IStorage>
#include <lvfs-core/tools/events/MouseEventHandler>
#include <lvfs-core/tools/events/MouseEventSource>
#include <lvfs-core/tools/events/KeyboardEventHandler>
#include <lvfs-core/tools/events/KeyboardEventSource>
#include <lvfs-core/tools/widgets/NestedWidget>
#include "../model/lvfs_db_EditableValueListModel.h"
#include "../../../model/lvfs_db_ValueListProxyModel.h"


using namespace ::LVFS;
using namespace ::LVFS::Db;
using namespace ::LVFS::Tools;

class PLATFORM_MAKE_PRIVATE EditableValueListWidgetPrivate : public QWidget
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
                    EditableValueListWidgetPrivate
                >
            > LineEditHandler;

public:
    EditableValueListWidgetPrivate(ICallback *callback, EventHandler *handler, const Interface::Adaptor<IStorage> &container, const EntityValueReader &reader);

    const Interface::Adaptor<IStorage> &container() const { return m_container; }
    Interface::Adaptor<IStorage> &container() { return m_container; }

    const Entity &entity() const { return m_entity; }

    const TreeView &view() const { return m_view; }
    TreeView &view() { return m_view; }

    const EditableValueListModel &model() const { return m_model; }
    EditableValueListModel &model() { return m_model; }

    const ValueListProxyModel &proxy() const { return m_proxy; }
    ValueListProxyModel &proxy() { return m_proxy; }

    QModelIndex currentIndex() const { return m_proxy.mapToSource(m_view.selectionModel()->currentIndex()); }

    void addValue();
    void removeValue();
//    void select(const QModelIndex &index);
    void setFocusToFilter() { m_filter.setFocus(); }

private Q_SLOTS:
    void setFilter();
    void clearFilter();
    void selectValue(const QModelIndex &index);

private:
    void setCurrentIndex(const QModelIndex &index) const;

private:
    ICallback *m_callback;
    Interface::Adaptor<IStorage> m_container;
    const Entity &m_entity;

    QVBoxLayout m_vLayout;
    QHBoxLayout m_hLayout;

    LineEditHandler m_handler;
    LineEdit m_filter;
    QPushButton m_search;

    TreeView m_view;
    EditableValueListModel m_model;
    ValueListProxyModel m_proxy;
};


class PLATFORM_MAKE_PRIVATE MainEditableValueListWidget : public BaseNestedWidget, public EditableValueListWidgetPrivate::ICallback
{
public:
    MainEditableValueListWidget(EventHandler *handler, const Interface::Adaptor<IStorage> &container, const EntityValueReader &reader, NestedDialog *parent);

    /* BaseNestedWidget */
    virtual QWidget *centralWidget();
    virtual void setReadOnly(bool value);
    virtual void setFocus();

    /* EditableValueListWidgetPrivate::ICallback */
    virtual void acceptAndClose();
    virtual NestedDialog *parent();
    virtual void critical(const QString &text);

    const Interface::Adaptor<IStorage> &container() const { return m_private.container(); }
    Interface::Adaptor<IStorage> &container() { return m_private.container(); }

    const Entity &entity() const { return m_private.entity(); }

    QModelIndex currentIndex() const { return m_private.currentIndex(); }
    EntityValue takeValue() { return m_private.model().take(currentIndex()); }

    void closeDbContext() { m_private.model().close(); }

    void addValue() { m_private.addValue(); }
    void removeValue() { m_private.removeValue(); }
//    void select(const QModelIndex &index) { m_private.select(index); }
    void setFocusToFilter() { m_private.setFocusToFilter(); }
    void setViewToolTip(const QString &value) { m_private.view().setToolTip(value); }

private:
    EditableValueListWidgetPrivate m_private;
};


class PLATFORM_MAKE_PRIVATE EditableValueListWidget : public NestedWidget, public EditableValueListWidgetPrivate::ICallback
{
public:
    EditableValueListWidget(const Interface::Adaptor<IStorage> &container, const EntityValueReader &reader, NestedDialog *parent);

    /* BaseNestedWidget */
    virtual void setFocus();

    /* EditableValueListWidgetPrivate::ICallback */
    virtual void acceptAndClose();
    virtual NestedDialog *parent();
    virtual void critical(const QString &text);

    const Interface::Adaptor<IStorage> &container() const { return m_private.container(); }
    Interface::Adaptor<IStorage> &container() { return m_private.container(); }

    QModelIndex currentIndex() const { return m_private.currentIndex(); }
    EntityValue takeValue() { return m_private.model().take(currentIndex()); }

    void addValue();
    void removeValue();
//    void select(const QModelIndex &index) { m_private.select(index); }
    void setFocusToFilter();

private:
    typedef KeyboardEventHandler<
                EventHandlerBase<
                    EditableValueListWidget
                >
            > TreeViewHandler;

private:
    TreeViewHandler m_handler;
    EditableValueListWidgetPrivate m_private;
};

#endif /* LVFS_DB_EDITABLEVALUELISTWIDGET_H_ */
