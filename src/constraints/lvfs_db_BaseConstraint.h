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

#ifndef LVFS_DB_BASECONSTRAINT_H_
#define LVFS_DB_BASECONSTRAINT_H_

#include <QtCore/QSharedData>
#include <liquiddb/EntityConstraint>
#include <efc/Holder>


namespace LVFS {
namespace Db {

class BaseConstraint : public ::EFC::Holder<BaseConstraint>::Data
{
public:
    typedef ::EFC::Holder<BaseConstraint> Holder;

public:
	BaseConstraint(BaseConstraint *parent = 0);
	virtual ~BaseConstraint();

	BaseConstraint *parent() const { return m_parent; }

	virtual bool isGroup() const = 0;
	virtual const LiquidDb::Constraint &constraint() const = 0;

private:
	BaseConstraint *m_parent;
};

}}

#endif /* LVFS_DB_BASECONSTRAINT_H_ */
