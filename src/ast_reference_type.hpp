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

#ifndef J4A__AST_REFERENCE_TYPE__HPP
#define J4A__AST_REFERENCE_TYPE__HPP

#include "ast__def.hpp"
#include "ast_type.hpp"

NS_AST_BEGIN

class ReferenceType: public Type
{
public:
    AST_IMPLEMENT(ReferenceType);
    AST_CREATE_NAMED___(ReferenceType, Type);
    AST_CREATE_POINTER_(ReferenceType, Type, Identifier);

public:
    virtual bool is_reference_type() override {return true;}
    virtual bool is_void_type() override {return false;}
    virtual bool is_string_type() override;

    virtual j4a::string get_c_type() override;
    virtual j4a::string get_c_sign_in_method() override;
    virtual j4a::string get_c_default_value() override {return "NULL";}

    virtual j4a::string get_c_call_instance_method_api() override   {return "CallObjectMethod";}
    virtual j4a::string get_c_call_static_method_api() override     {return "CallStaticObjectMethod";}
    virtual j4a::string get_c_get_instance_field_api() override     {return "GetObjectField";}
    virtual j4a::string get_c_get_static_field_api() override       {return "GetStaticObjectField";}
    virtual j4a::string get_c_set_instance_field_api() override     {return "SetObjectField";}
    virtual j4a::string get_c_set_static_field_api() override       {return "SetStaticObjectField";}

private:
    j4a::string _get_java_long_name();
};

NS_AST_END

#endif
