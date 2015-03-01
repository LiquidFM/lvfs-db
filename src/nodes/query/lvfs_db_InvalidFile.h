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

#ifndef WORKSPACE_LVFS_DB_SRC_NODES_QUERY_LVFS_DB_INVALIDFILE_H_
#define WORKSPACE_LVFS_DB_SRC_NODES_QUERY_LVFS_DB_INVALIDFILE_H_

#include <lvfs/IEntry>


namespace LVFS {
namespace Db {

class PLATFORM_MAKE_PRIVATE InvalidFile : public Implements<IEntry>
{
public:
    InvalidFile(const char *file);
    virtual ~InvalidFile();

public: /* IEntry */
    virtual const char *title() const;
    virtual const char *schema() const;
    virtual const char *location() const;
    virtual const IType *type() const;
    virtual Interface::Holder open(IFile::Mode mode) const;

private:
    char *m_title;
    Interface::Holder m_type;
};

}}

#endif /* WORKSPACE_LVFS_DB_SRC_NODES_QUERY_LVFS_DB_INVALIDFILE_H_ */
