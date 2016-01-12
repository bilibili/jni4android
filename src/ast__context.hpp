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

#ifndef J4A__AST__CONTEXT__HPP
#define J4A__AST__CONTEXT__HPP

#include "ast__def.hpp"
#include "ast__namespace.hpp"
#include "ast_identifier.hpp"
#include <deque>
#include <map>
#include <string>

NS_AST_BEGIN

class QualifiedIdentifier;
class Class;

class Context
{
public:
    typedef std::vector<Namespace*>         NamespaceStack;
    typedef std::deque<Node::pointer_type>  NodePool;

    AST_PROPERTY_DEFINE(std::string,        h_file_path);
    AST_PROPERTY_DEFINE(std::string,        c_file_path);
    AST_PROPERTY_DEFINE(std::string,        j4a_include_file_path);
    AST_PROPERTY_DEFINE(std::string,        j4a_loader_file_path);
    AST_PROPERTY_DEFINE(std::string,        java_class_dir);
    AST_PROPERTY_DEFINE(Namespace*,         global_name_space);

public:
    void add_java_package(const char *package_name);

    Identifier *find_identifier(Node *node, const j4a::string& name);

    Namespace *get_local_namespace();
    void push_local_namespace(Namespace *local_namespace);
    void pop_local_namespace();

    j4a::string get_sign_in_method(j4a::string name);

    template <class T>
    T* put(T *node)
    {
        m_node_pool.push_back(node);
        return node;
    }

private:
    Context() {
        Namespace *global_namespace = new Namespace();
        set_global_name_space(global_namespace);
    }

public:
    static Context *instance() {
        if (!s_instance) {
            s_instance = new Context();
        }
        return s_instance;
    }

private:
    NamespaceStack  m_namespace_stack;
    NodePool        m_node_pool;
    static Context *s_instance;
};

NS_AST_END

#endif
