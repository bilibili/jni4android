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

#ifndef J4A__AST_MEMBER__HPP
#define J4A__AST_MEMBER__HPP

#include <set>
#include <ostream>
#include "ast__def.hpp"
#include "ast_node.hpp"
#include "ast_identifier.hpp"
#include "ast_annotation.hpp"
#include "ast_modifier.hpp"
#include "ast_type.hpp"

NS_AST_BEGIN

class Member: public Identifier
{
public:
    AST_IMPLEMENT_ABSTRACT(Member);
    AST_CREATE_NAMED____ABSTRACT(Member, Identifier);
    AST_CREATE_POINTER__ABSTRACT(Member, Identifier, Identifier);

    AST_CHILD_DEFINE(Annotations,   annotations);
    AST_CHILD_DEFINE(ModifierSet,   modifier_set);
    AST_CHILD_DEFINE(Type,          type);

    AST_GETTER_DECL_0(j4a::string,  c_jni_sign);
    AST_GETTER_DECL_0(j4a::string,  c_jni_id_name);
    AST_GETTER_DECL(j4a::string,    c_jni_id);
    AST_PROPERTY_DEFINE(int,        build_indent) = 0;

public:
    Annotation *get_annotation_at(const char *name) {
        return get_annotations()->get_at(name).get();
    }

    bool is_public()    {return get_modifier_set()->has_token(T_PUBLIC);}
    bool is_private()   {return get_modifier_set()->has_token(T_PRIVATE);}
    bool is_protected() {return get_modifier_set()->has_token(T_PROTECTED);}
    bool is_static()    {return get_modifier_set()->has_token(T_STATIC);}
    bool is_final()     {return get_modifier_set()->has_token(T_FINAL);}

    void reset_build_format() {
        set_build_indent(0);
    }

    void increase_build_indent(int increase) {
        set_build_indent(get_build_indent() + increase);
    }

    j4a::fill build_indent() {return j4a::fill(' ', get_build_indent());}

public:
    // .h files
    virtual void build_c_func_decl(std::ostream &os) {;}
    virtual void build_c_simple_func_decl(std::ostream &os) {;}

    // .c files
    virtual void build_c_class_decl(std::ostream &os) {;}
    virtual void build_c_member_id_decl(std::ostream &os) {;}
    virtual void build_c_member_id_load(std::ostream &os) {;}
    virtual void build_c_func_impl(std::ostream &os) {;}
};


class MemberList: public NodeList<Member>
{
public:
    AST_IMPLEMENT(MemberList);
    AST_CREATE_NONAME__(MemberList, NodeList<Member>);

    // class Node
    virtual void debug_print(int indent) override {
        iterator begin = this->begin();
        iterator end   = this->end();

        for (NULL; begin != end; ++begin) {
            (*begin)->debug_print(indent);
        }
    }

    // .h files
    void build_all_c_func_decl(std::ostream &os);
    void build_all_c_simple_func_decl(std::ostream &os);

    // .c files
    void build_all_c_class_decl(std::ostream &os);
    void build_all_c_member_id_decl(std::ostream &os);
    void build_all_c_member_id_load(std::ostream &os);
    void build_all_c_func_impl(std::ostream &os);
};

NS_AST_END

#endif
