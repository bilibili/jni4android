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

#ifndef J4A__AST_METHOD__HPP
#define J4A__AST_METHOD__HPP

#include "ast__def.hpp"
#include "ast_member.hpp"
#include "ast_argument.hpp"

NS_AST_BEGIN

class Method: public Member
{
public:
    AST_IMPLEMENT(Method);
    AST_CREATE_NAMED___(Method, Member);

    AST_CHILD_DEFINE(ArgumentList,      argument_list);

    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_jni_sign);
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_jni_id_name);
    AST_GETTER_DECL(j4a::string,            c_jni_method_name);

    AST_GETTER_DECL(j4a::string,            c_call_api);
    AST_GETTER_DECL(j4a::string,            c_call_object_id);
    AST_GETTER_DECL(j4a::string,            c_call_method_id);
    AST_GETTER_DECL(bool,                   c_call_need_this);

private:
    static const int FLAG_NORMAL;
    static const int FLAG_CATCH_ALL;
    static const int FLAG_WITH_C_STRING;
    static const int FLAG_AS_GLOBAL_REF;
    static const int FLAG_AS_C_BUFFER;
    static const int FLAG_SIMPLE_NAME;

    bool _has_string_arg();

    void _build_class_id(std::ostream &os);
    void _build_c_call_jni_statement(std::ostream &os, int flags);
    void _build_c_func_name(std::ostream &os, int flags);
    void _build_c_func_decl_statement(std::ostream &os, int flags);
    void _build_c_func_call_statement(std::ostream &os, int flags);
    void _build_c_func_string_argument_cast_statements(std::ostream &os, int flags);
    void _build_c_func_string_argument_release_statements(std::ostream &os, int flags);
    void _build_c_func_impl_void_type_statement(std::ostream &os, int flags);
    void _build_c_func_impl_reference_type_statement(std::ostream &os, int flags);
    void _build_c_func_impl_primitive_type_statement(std::ostream &os, int flags);

public:
    virtual void build_c_func_decl(std::ostream &os) override;
    virtual void build_c_simple_func_decl(std::ostream &os) override;
    // virtual void build_c_class_decl(std::ostream &os);
    virtual void build_c_member_id_decl(std::ostream &os) override;
    virtual void build_c_member_id_load(std::ostream &os) override;
    virtual void build_c_func_impl(std::ostream &os) override;

    // class Node
    // @Override
    virtual Method *get_this_method() override {return this;}
    // @Override
    virtual void debug_print(int indent) override {
        std::cout << j4a::fill(' ', indent);

        get_modifier_set()->debug_print(0);
        get_type()->debug_print(0);
        std::cout << " " << get_name() << "(";
        get_argument_list()->debug_print(0);
        std::cout << ");" << std::endl;
    }

private:
    typedef std::map<j4a::string, j4a::string> SimpleNameMap;
    std::map<j4a::string, j4a::string> m_simple_name_map;
};

NS_AST_END

#endif
