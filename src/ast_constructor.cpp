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

#include "ast_constructor.hpp"
#include "ast_class.hpp"

using namespace ast;

j4a::string Constructor::get_c_jni_sign()
{
    std::ostringstream os;
    os << "(";

    ArgumentList::iterator begin = get_argument_list()->begin();
    ArgumentList::iterator end   = get_argument_list()->end();
    for (NULL; begin != end; ++begin) {
        os << (*begin)->get_type()->get_c_sign_in_method();
    }

    os << ")V";
    return os;
}

j4a::string Constructor::get_c_jni_id_name()
{
    std::ostringstream os;
    os << "constructor_" << get_name();
    return os;
}

j4a::string Constructor::get_c_jni_method_name()
{
    return "<init>";
}

j4a::string Constructor::get_c_call_api()
{
    return "NewObject";
}

j4a::string Constructor::get_c_call_object_id()
{
    return get_this_class()->get_c_jni_id();
}

bool Constructor::get_c_call_need_this()
{
    return false;
}
