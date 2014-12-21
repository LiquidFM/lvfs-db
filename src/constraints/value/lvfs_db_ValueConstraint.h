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

#ifndef LVFS_DB_VALUECONSTRAINT_H_
#define LVFS_DB_VALUECONSTRAINT_H_

#include "../lvfs_db_BaseConstraint.h"


namespace LVFS {
namespace Db {

using namespace LiquidDb;


class ValueConstraint : public BaseConstraint
{
public:
    ValueConstraint(const Entity::Property &property, Constraint::Operator op, const EntityValue &value, BaseConstraint *parent = 0);

	/* BaseConstraint */
	virtual bool isGroup() const;
    virtual const Constraint &constraint() const;

	const Entity::Property &property() const { return m_property; }
	Constraint::Operator op() const { return m_constraint.op(); }
	const EntityValue &value() const { return m_constraint.value(); }

private:
	Entity::Property m_property;
	EntityConstraint m_constraint;
};

}}

#endif /* LVFS_DB_VALUECONSTRAINT_H_ */
