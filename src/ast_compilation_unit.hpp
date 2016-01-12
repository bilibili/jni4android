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

#ifndef J4A__AST_COMPILATION_UNIT__HPP
#define J4A__AST_COMPILATION_UNIT__HPP

#include "ast__def.hpp"
#include "ast__namespace.hpp"
#include "ast_identifier.hpp"
#include "ast_import.hpp"
#include "ast_class.hpp"

NS_AST_BEGIN

class CompilationUnit: public Node
{
public:
    AST_IMPLEMENT(CompilationUnit);
    AST_CREATE_NONAME__(CompilationUnit, Node);

    AST_PROPERTY_DEFINE(Namespace*,     local_namespace) = new Namespace();

    AST_CHILD_DEFINE(ImportList,        import_list);
    AST_CHILD_DEFINE(Class,             clazz);
    AST_CHILD_DEFINE(Identifier,        package);

public:
    j4a::string get_header_macro() {
        std::ostringstream os;
        os << "J4A__";
        os << get_package()->get_c_long_name();
        os << "_";
        os << get_clazz()->get_name();
        os << "__H";
        return os;
    }

    j4a::string get_include_path() {
        std::ostringstream os;
        os << "j4a/class/";
        os << get_package()->get_fs_long_path();
        os << "/";
        os << get_clazz()->get_name();
        os << ".h";
        return os;
    }

    void do_build(std::ostream&, std::ostream&, std::ostream&, std::ostream&);
    void build();

public:
    // @Override
    virtual CompilationUnit *get_this_compilation_unit() override {return this;}
    // output
    virtual void debug_print(int indent) override {
        get_package()->debug_print(0);
        printf(";\n");
        get_import_list()->debug_print(0);
        printf("\n");
        get_clazz()->debug_print(0);
        printf("\n");
    }
};

NS_AST_END

#endif
