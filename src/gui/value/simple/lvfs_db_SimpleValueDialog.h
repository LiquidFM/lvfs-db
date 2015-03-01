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

#ifndef LVFS_DB_SIMPLEVALUEDIALOG_H_
#define LVFS_DB_SIMPLEVALUEDIALOG_H_

#include <lvfs-core/tools/widgets/NestedPlainDialog>
#include "widgets/lvfs_db_SimpleValueWidget.h"
#include "../../lvfs_db_common.h"


template <LVFS::Db::Entity::Type EntityType>
class PLATFORM_MAKE_PRIVATE SimpleValueDialog : public NestedPlainDialog
{
public:
    typedef typename EntityValueType<EntityType>::type value_type;
    typedef ValueDialog<value_type>                    base_class;

public:
    SimpleValueDialog(const QString &title, QWidget *parent = 0) :
        NestedPlainDialog(parent)
    {
        setWindowTitle(title);
        setCentralWidget(&m_mainWidget);
    }

    value_type value() const { return m_mainWidget.value(); }

private:
    MainSimpleValueWidget<value_type> m_mainWidget;
};

#endif /* LVFS_DB_SIMPLEVALUEDIALOG_H_ */
