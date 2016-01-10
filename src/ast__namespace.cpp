/*
 * copyright (c) 2015 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of jni4android.
 *
 * jni4android is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * jni4android is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with jni4android; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "ast__namespace.hpp"
#include <dirent.h>
#include <cstring>
#include "ast__context.hpp"
#include "ast_class.hpp"

using namespace ast;

void Namespace::add_package_identifier(Identifier *package_identifier)
{
    DIR *d;
    struct dirent *dir;

    assert(package_identifier);
    d = opendir(Context::instance()->get_java_class_dir().c_str());
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            const char *ext = strchr(dir->d_name, '.');
            if (ext && 0 == strcmp(ext, ".java")) {
                j4a::string class_name(dir->d_name, ext - dir->d_name);
                add_class_identifier(Identifier::create_with_prefix(class_name, package_identifier));
            }
        }
        closedir(d);
    }
}

void Namespace::add_class_identifier(Identifier *class_identifier)
{
    j4a::string name        = class_identifier->get_name();
    j4a::string full_name   = class_identifier->get_java_long_name();
    m_id_map[name]      = class_identifier;
    m_id_map[full_name] = class_identifier;

    Identifier::pointer_type outer_class = class_identifier->get_outer_class_identifier();
    if (!outer_class)
        return;

    Identifier::pointer_type inner_identifier = Identifier::create(class_identifier->get_name());
    Identifier::pointer_type outer_identifier = inner_identifier;
    while (outer_class) {
        outer_identifier->set_prefix(Identifier::create(outer_class->get_name()));
        outer_identifier = outer_identifier->get_prefix();

        j4a::string relative_name = inner_identifier->get_java_long_name();
        Identifier::pointer_type relative_identifier = Identifier::create_by_split(relative_name.c_str());
        m_id_map[relative_name] = relative_identifier;

        outer_class = outer_class->get_outer_class_identifier();
    }
}

Identifier *Namespace::find_identifier(const j4a::string &name)
{
    IdentifierMap::iterator find = m_id_map.find(name);
    return find == m_id_map.end() ? NULL : find->second.get();
}
