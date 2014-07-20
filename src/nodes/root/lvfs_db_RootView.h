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

#ifndef LVFS_DB_ROOTVIEW_H_
#define LVFS_DB_ROOTVIEW_H_

#include <QtGui/QTreeView>
#include <lvfs-core/IView>


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE RootView : public Implements<Core::IView>
{
public:
    RootView();
    virtual ~RootView();

    virtual QWidget *widget() const;
    virtual void setMainView(const Interface::Holder &mainView);

    virtual const Interface::Holder &node() const;
    virtual bool setNode(const Interface::Holder &node);

private:
    inline bool openNode(const Interface::Holder &node, const QModelIndex &currentIdx, const QModelIndex &parentIdx);

private:
    Interface::Holder m_node;
    Interface::Holder m_mainView;

private:
    QTreeView m_view;
};

}}

#endif /* LVFS_DB_ROOTVIEW_H_ */
