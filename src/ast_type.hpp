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

#ifndef J4A__AST_TYPE__HPP
#define J4A__AST_TYPE__HPP

#include "ast__def.hpp"
#include "ast_identifier.hpp"

NS_AST_BEGIN

class Type: public Identifier
{
public:
    AST_IMPLEMENT_ABSTRACT(Type);
    AST_CREATE_NAMED____ABSTRACT(Type, Identifier);

    AST_PROPERTY_DEFINE(bool, is_array) = false;
protected:
    explicit Type(Node *other): Identifier(other) {init(other);}
private:
    void init(Node *other) {
        if (other) {
            Type *other_ = dynamic_cast<Type *>(other);
            if (other_)
                set_is_array(other_->get_is_array());
        }
    }

    AST_GETTER_DECL_0(j4a::string, c_type);
    AST_GETTER_DECL_0(j4a::string, c_sign_in_method);
    AST_GETTER_DECL_0(j4a::string, c_default_value);

    AST_GETTER_DECL_0(j4a::string, c_call_instance_method_api);
    AST_GETTER_DECL_0(j4a::string, c_call_static_method_api);
    AST_GETTER_DECL_0(j4a::string, c_get_instance_field_api);
    AST_GETTER_DECL_0(j4a::string, c_get_static_field_api);
    AST_GETTER_DECL_0(j4a::string, c_set_instance_field_api);
    AST_GETTER_DECL_0(j4a::string, c_set_static_field_api);

public:
    virtual bool is_reference_type() = 0;
    virtual bool is_void_type() = 0;
    virtual bool is_string_type() = 0;

    // @Override
    virtual void debug_print(int indent) override {
        if (get_is_array()) {
            std::cout << get_name() << "[]" << std::endl;
        } else {
            std::cout << get_name();
        }
    }
};

NS_AST_END

#endif
