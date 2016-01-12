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

#ifndef J4A__AST_CLASS__HPP
#define J4A__AST_CLASS__HPP

#include "ast__def.hpp"
#include "ast__namespace.hpp"
#include "ast_member.hpp"

NS_AST_BEGIN

class Class: public Member
{
public:
    AST_IMPLEMENT(Class);
    AST_CREATE_NAMED___(Class, Member);
    AST_CREATE_POINTER_(Class, Member, Identifier);

    AST_PROPERTY_DEFINE(Namespace*,     local_namespace) = new Namespace();
    AST_PROPERTY_DEFINE(bool,           is_interface)    = false;

    AST_CHILD_DEFINE(MemberList,        member_list);

    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_jni_sign);
    AST_GETTER_DECL_OVERRIDE(j4a::string,   c_jni_id_name);

public:
    j4a::string get_c_jni_class_instance() {
        std::ostringstream os;
        os << "class_" << get_c_class_name();
        return os;
    }

    bool need_c_simple_class_name() {
        return get_annotation_at("SimpleCClassName") != NULL;
    }

public:
    // class Member
    // @Override
    virtual void build_c_func_decl(std::ostream &os) override;
    virtual void build_c_simple_func_decl(std::ostream &os) override;
    // @Override
    virtual void build_c_class_decl(std::ostream &os) override;
    // @Override
    // virtual void build_c_member_id_decl(std::ostream &os) override;
    // @Override
    virtual void build_c_member_id_load(std::ostream &os) override;
    // @Override
    virtual void build_c_func_impl(std::ostream &os) override;

    // class Identifier
    virtual j4a::string get_java_long_name() override {
        if (get_parent()) {
            std::ostringstream os;
            if (get_parent()->get_this_class()) {
                // inner class
                os << get_parent()->get_this_class()->get_java_long_name();
                os << "$";
            } else {
                os << get_parent()->get_this_package()->get_java_long_name();
                os << ".";
            }
            os << get_name();
            return os;
        } else {
            return Member::get_java_long_name();
        }
    }

    // class Node
    // @Override
    virtual Class *get_this_class() override {return this;}

    j4a::string get_c_class_name(bool with_prefix = true) {
        std::ostringstream os;
        if (get_parent()->get_this_class()) {
            // inner class
            os << get_parent()->get_this_class()->get_c_class_name();
            os << "__";
        } else {
            if (with_prefix) {
                os << "J4AC_";
            }
            os << get_this_package()->get_c_long_name();
            os << "_";
        }
        os << get_name();
        return os;
    }

    j4a::string get_c_simple_class_name() {
        std::ostringstream os;
        if (get_parent()->get_this_class()) {
            // inner class
            os << get_parent()->get_this_class()->get_c_simple_class_name();
            os << "__";
        } else {
            os << "J4AC_";
        }
        os << get_name();
        return os;
    }

    // @Override
    virtual void debug_print(int indent) override {
        get_annotations()->debug_print(indent);
        get_modifier_set()->debug_print(indent);
        if (get_is_interface()) {
            std::cout << "class ";
        } else {
            std::cout << "interface ";
        }
        std::cout << get_name() << " " << std::endl;
        get_member_list()->debug_print(indent + 4);
        std::cout << j4a::fill(' ', indent) << "};" << std::endl;
    }
};

NS_AST_END

#endif
