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

#ifndef LVFS_DB_GROUPCONSTRAINT_H_
#define LVFS_DB_GROUPCONSTRAINT_H_

#include <efc/Vector>
#include <QtCore/QCoreApplication>
#include "../lvfs_db_BaseConstraint.h"


namespace LVFS {
namespace Db {


class GroupConstraint : public BaseConstraint
{
	Q_DECLARE_TR_FUNCTIONS(GroupConstraint)

public:
	typedef ::EFC::Vector<Holder>     Container;
    typedef Container::iterator       iterator;
	typedef Container::const_iterator const_iterator;
	enum { InvalidIndex = -1 };

public:
	GroupConstraint(LiquidDb::GroupConstraint::Type type = LiquidDb::GroupConstraint::And, BaseConstraint *parent = 0);

	/* BaseConstraint */
	virtual bool isGroup() const;
    virtual const LiquidDb::Constraint &constraint() const;

	LiquidDb::GroupConstraint::Type type() const { return m_constraint.type(); }
	void setType(LiquidDb::GroupConstraint::Type type) { m_constraint.setType(type); }

    iterator begin() { return m_items.begin(); }
	const_iterator begin() const { return m_items.begin(); }
    iterator end() { return m_items.end(); }
    const_iterator end() const { return m_items.end(); }

    Container::size_type size() const { return m_items.size(); }
    const Holder &at(Container::size_type index) const { return m_items[index]; }
    Container::size_type indexOf(BaseConstraint *item) const;

	void add(const BaseConstraint::Holder &constraint);
	void insert(Container::size_type index, const BaseConstraint::Holder &constraint);
	void swap(Container::size_type index1, Container::size_type index2);
	void remove(Container::size_type index);

protected:
	Container m_items;
	LiquidDb::GroupConstraint m_constraint;
};

}}

#endif /* LVFS_DB_GROUPCONSTRAINT_H_ */
