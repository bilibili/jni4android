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

#ifndef J4A__AST_PROPERTY_ACCESSOR__HPP
#define J4A__AST_PROPERTY_ACCESSOR__HPP

#include "ast__def.hpp"
#include "ast_method.hpp"
#include "ast_field.hpp"
#include "ast_primitive_type.hpp"

NS_AST_BEGIN

class PropertyAccessor: public Method
{
public:
    AST_IMPLEMENT_ABSTRACT(PropertyAccessor);
    AST_CREATE_NAMED____ABSTRACT(PropertyAccessor, Method)

    AST_PROPERTY_DEFINE(Field*, field);

public:
    void setup_for_field(Field* field)
    {
        set_field(field);

        set_annotations(field->get_annotations());
        set_modifier_set(field->get_modifier_set());
        set_parent(field->get_parent());
    }
};




class PropertyGetter: public PropertyAccessor
{
public:
    AST_IMPLEMENT(PropertyGetter);
    AST_CREATE_NAMED___(PropertyGetter, PropertyAccessor)

    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_call_api);
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_call_method_id);

public:
    static PropertyGetter *create_for_field(Field *field)
    {
        PropertyGetter *getter = create(field->get_name() + "__get");
        getter->setup_for_field(field);

        getter->set_type(field->get_type());
        getter->set_argument_list(ArgumentList::create());
        return getter;
    }
};



class PropertySetter: public PropertyAccessor
{
public:
    AST_IMPLEMENT(PropertySetter);
    AST_CREATE_NAMED___(PropertySetter, PropertyAccessor)

    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_call_api);
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_call_method_id);

public:
    static PropertySetter *create_for_field(Field *field)
    {
        PropertySetter *setter = create(field->get_name() + "__set");
        setter->setup_for_field(field);

        setter->set_type(VoidType::create());

        Argument::pointer_type argument = Argument::create("value");
        argument->set_type(field->get_type());

        ArgumentList::pointer_type argument_list = ArgumentList::create();
        argument_list->push_back(argument);

        setter->set_argument_list(argument_list);

        return setter;
    }
};

NS_AST_END

#endif
