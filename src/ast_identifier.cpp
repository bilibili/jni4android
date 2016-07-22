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

#include "ast_identifier.hpp"
#include "ast__context.hpp"
#include <cstring>

using namespace ast;

Identifier* Identifier::create(const j4a::string& name)
{
    Identifier* identifier = new Identifier(name);
    identifier->put_in_pool();
    return identifier;
}

Identifier* Identifier::create_with_prefix(const j4a::string& name, Identifier *parent)
{
    Identifier* identifier = create(name);
    identifier->set_prefix(parent);
    return identifier;
}

Identifier* Identifier::create_by_split(const char *long_name, char separator)
{
    Identifier* identifier = NULL;

    const char *lookup = long_name;
    const char *next   = strchr(lookup, separator);
    while (next && next > lookup) {
        j4a::string child_id = j4a::string(lookup, next - lookup);

        identifier = create_with_prefix(child_id, identifier);

        lookup = next + 1;
        next   = strchr(lookup, separator);
    }

    if (*lookup) {
        identifier = create_with_prefix(lookup, identifier);
    }

    return identifier;
}


Identifier::pointer_type Identifier::get_outer_class_identifier()
{
    Identifier::pointer_type prefix = get_prefix();
    if (!prefix)
        return NULL;

    if (prefix->is_class_identifier())
        return prefix;

    return prefix->get_outer_class_identifier();
}

j4a::string Identifier::get_java_long_name()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_java_long_name();
        os << ".";
    }

    os << get_name();
    return j4a::string(os);
}

j4a::string Identifier::get_c_long_name()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_c_long_name();
        os << "_";
    }

    os << get_name();
    return j4a::string(os);
}

j4a::string Identifier::get_c_jni_sign()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_c_jni_sign();
        os << "/";
    }

    os << get_name();
    return os.str();
}

j4a::string Identifier::get_fs_long_path()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_fs_long_path();
        os << "/";
    }

    os << get_name();
    return os.str();
}



j4a::string ClassIdentifier::get_c_jni_sign()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_c_jni_sign();
        if (get_outer_class_identifier())
            os << "$";
        else
            os << "/";
    }

    os << get_name();
    return os.str();
}
