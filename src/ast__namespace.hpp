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

#ifndef J4A__AST__NAMESPACE__HPP
#define J4A__AST__NAMESPACE__HPP

#include "ast__def.hpp"
#include "ast_identifier.hpp"

NS_AST_BEGIN

class Namespace
{
public:
    AST_PROPERTY_DEFINE(Identifier::pointer_type, identifier);

public:
    typedef std::map<j4a::string, Identifier::pointer_type> IdentifierMap;
    typedef IdentifierMap::iterator iterator;

    iterator begin() {return m_id_map.begin();}
    iterator end()   {return m_id_map.end();}

    void add_package_identifier(Identifier *package_identifier);
    void add_class_identifier(Identifier *class_identifier);
    template<class T>
    void add_class_identifiers(T begin, T end) {
        for (NULL; begin != end; ++begin) {
            add_class_identifier(*begin);
        }
    }

    Identifier *find_identifier(const j4a::string &name);

    void clear() {m_id_map.clear();}

private:
    IdentifierMap m_id_map;
};

NS_AST_END

#endif
