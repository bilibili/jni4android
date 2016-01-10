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

#ifndef J4A__AST_CONSTRUCTOR__HPP
#define J4A__AST_CONSTRUCTOR__HPP

#include "ast__def.hpp"
#include "ast_method.hpp"
#include "ast_field.hpp"

NS_AST_BEGIN

class Constructor: public Method
{
public:
    AST_IMPLEMENT(Constructor);
    AST_CREATE_NAMED___(Constructor, Method);
    
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_jni_sign);
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_jni_id_name);
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_jni_method_name);

    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_call_api);
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_call_object_id);
    AST_GETTER_DECL_OVERRIDE(bool,          c_call_need_this);

public:
    virtual void debug_print(int indent) override {
        std::cout << j4a::fill(' ', indent);

        get_modifier_set()->debug_print(0);
        std::cout << get_name() << "(";
        get_argument_list()->debug_print(0);
        std::cout << ");" << std::endl;
    }
};

NS_AST_END

#endif
