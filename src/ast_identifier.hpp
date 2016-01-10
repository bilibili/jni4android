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

#ifndef J4A__AST_QUALIFIED_IDNETIFIER__HPP
#define J4A__AST_QUALIFIED_IDNETIFIER__HPP

#include "ast_node.hpp"

NS_AST_BEGIN

class Identifier: public Node
{
public:
    AST_IMPLEMENT(Identifier);

    AST_PROPERTY_DEFINE(pointer_type,   prefix);
    AST_GETTER_DEFINE(j4a::string,      name);

    AST_GETTER_DECL(pointer_type,       outer_class_identifier);
    AST_GETTER_DECL(j4a::string,        java_long_name);
    AST_GETTER_DECL(j4a::string,        c_long_name);
    AST_GETTER_DECL(j4a::string,        c_jni_sign);
    AST_GETTER_DECL(j4a::string,        fs_long_path);

    virtual bool is_class_identifier() {return false;}

public:
    virtual void debug_print(int indent) override {
        if (get_prefix()) {
            get_prefix()->debug_print(indent);
            std::cout << "." << std::endl;
        }
        std::cout << get_name();
    }

protected:
    explicit Identifier(const j4a::string &name): AST_PROPERTY(name)(name) {init(NULL);}
    explicit Identifier(Node *other): Node(other) {init(other);}
private:
    void init(Node *other) {
        if (other) {
            Identifier *other_ = dynamic_cast<Identifier *>(other);
            if (other_) {
                AST_PROPERTY(name) = other_->get_name();
                set_prefix(other_->get_prefix());
            }
        }
    }
public:
    static Identifier* create(const j4a::string& name);
    static Identifier* create_with_prefix(const j4a::string& name, Identifier *prefix);
    static Identifier* create_by_split(const char *long_name, char separator = '.');
};



template <class T>
class IdentifierMap: public Node
{
public:
    typedef j4a::string                                         key_type;
    typedef T                                                   element_type;
    typedef typename element_type::pointer_type                 element_pointer_type;
    typedef typename std::map<key_type, element_pointer_type>   container;
    typedef typename container::iterator                        iterator;

    iterator begin() {return m_node_map.begin();}
    iterator end()   {return m_node_map.end();}

    void insert(element_type        *node)  {_insert(node);}
    void insert(element_pointer_type node)  {_insert(node.get());}

    // void assign(NamedNodeMap *node_map) {m_node_map = node_map->m_node_map;}
    size_t size() {return m_node_map.size();}

    element_pointer_type get_at(const char *name)               {return _get_at(name);}
    element_pointer_type get_at(const j4a::string &name)        {return _get_at(name);}

private:
    container m_node_map;

private:
    element_pointer_type _get_at(const key_type &name) {
        iterator find = m_node_map.find(name);
        if (find == m_node_map.end())
            return element_pointer_type(NULL);
        return find->second;
    }

    void _insert(T *node) {
        key_type name = node->get_name();

        iterator find = m_node_map.find(name);
        assert(find == m_node_map.end());
        if (find != m_node_map.end()) {
            if (find->second)
                find->second->set_parent(NULL);
            find->second = node;
        } else {
            m_node_map.insert(std::make_pair(name, node));
        }

        node->set_parent(this);
    }

public:
    AST_IMPLEMENT_ABSTRACT(IdentifierMap);
protected:
    explicit IdentifierMap() {;}
    explicit IdentifierMap(IdentifierMap *other): Node(other) {
        iterator begin = this->begin();
        iterator end   = this->end();

        for (NULL; begin != end; ++begin) {
            insert(begin->second);
        }
    }
public:
    // static pointer_type make_ptr() {return pointer_type(new class__());}
};



class ClassIdentifier: public Identifier
{
public:
    AST_GETTER_DECL_OVERRIDE(j4a::string, c_jni_sign);

    virtual bool is_class_identifier() override {return true;}

public:
    AST_IMPLEMENT(ClassIdentifier);
protected:
    explicit ClassIdentifier(const j4a::string &name): Identifier(name) {init(NULL);}
    explicit ClassIdentifier(Node *other): Identifier(other) {init(other);}
private:
    void init(Node *other) {;}
public:
    static pointer_type make_ptr(const j4a::string &name) {return pointer_type(new ClassIdentifier(name));}
    static pointer_type make_ptr(Node *other) {return pointer_type(new ClassIdentifier(other));}
};

NS_AST_END

#endif
