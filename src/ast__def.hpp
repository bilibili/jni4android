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

#ifndef J4A__AST__DEF__HPP
#define J4A__AST__DEF__HPP

#include <iostream>
#include <map>
#include <vector>
#include "j4a.h"
#include "ast__forward.hpp"
#include "bison.j4a.tab.hpp"

#define AST_PROPERTY(name)              mm_##name
#define AST_MEMBER_DEFINE(type, name)   type AST_PROPERTY(name)

#define AST_GETTER_DECL_0(type, name)           public: virtual type get_##name() = 0;
#define AST_GETTER_DECL(type, name)             public: virtual type get_##name();
#define AST_GETTER_DECL_OVERRIDE(type, name)    public: virtual type get_##name() override;
#define AST_GETTER_IMPL(type, name)             public: virtual type get_##name()           {return AST_PROPERTY(name);}
#define AST_GETTER_IMPL_OVERRIDE(type, name)    public: virtual type get_##name() override  {return AST_PROPERTY(name);}
#define AST_GETTER_DEFINE(type, name)           public: AST_GETTER_IMPL(type, name);          private: AST_MEMBER_DEFINE(type, name)
#define AST_GETTER_DEFINE_OVERRIDE(type, name)  public: AST_GETTER_IMPL_OVERRIDE(type, name); private: AST_MEMBER_DEFINE_OVERRIDE(type, name)

#define AST_SETTER_DECL(type, name)             public: virtual void set_##name(type name);
#define AST_SETTER_DECL_OVERRIDE(type, name)    public: virtual void set_##name(type name) override;
#define AST_SETTER_IMPL(type, name)             public: virtual void set_##name(type name)          {AST_PROPERTY(name) = name;}
#define AST_SETTER_IMPL_OVERRIDE(type, name)    public: virtual void set_##name(type name) override {AST_PROPERTY(name) = name;}
#define AST_SETTER_DEFINE(type, name)           public: AST_SETTER_IMPL(type, name);          private: AST_MEMBER_DEFINE(type, name)
#define AST_SETTER_DEFINE_OVERRIDE(type, name)  public: AST_SETTER_IMPL_OVERRIDE(type, name); private: AST_MEMBER_DEFINE_OVERRIDE(type, name)

#define AST_PROPERTY_DECL(type, name)               AST_GETTER_DECL(type, name);          AST_SETTER_DECL(type, name);
#define AST_PROPERTY_DECL_OVERRIDE(type, name)      AST_GETTER_DECL_OVERRIDE(type, name); AST_SETTER_DECL_OVERRIDE(type, name);
#define AST_PROPERTY_IMPL(type, name)               AST_GETTER_IMPL(type, name);          AST_SETTER_IMPL(type, name);
#define AST_PROPERTY_IMPL_OEVRRIDE(type, name)      AST_GETTER_IMPL_OVERRIDE(type, name); AST_SETTER_IMPL_OVERRIDE(type, name);
#define AST_PROPERTY_DEFINE(type, name)             public: AST_PROPERTY_IMPL(type, name);          private: AST_MEMBER_DEFINE(type, name)
#define AST_PROPERTY_DEFINE_OVERRIDE(type, name)    public: AST_PROPERTY_IMPL_OVERRIDE(type, name); private: AST_MEMBER_DEFINE_OVERRIDE(type, name)



#define AST_CHILD_SETTER_DECL(type, name)           virtual void set_##name(type *name);
#define AST_CHILD_SETTER_DECL_OVERRIDE(type, name)  virtual void set_##name(type *name) override;
#define AST_CHILD_SETTER_IMPL(type, name)           virtual void set_##name(type *name)          {AST_PROPERTY(name).assign(name); name->set_parent(this);}
#define AST_CHILD_SETTER_IMPL_OVERRIDE(type, name)  virtual void set_##name(type *name) override {AST_PROPERTY(name).assign(name); name->set_parent(this);}
#define AST_CHILD_GETTER_DECL(type, name)           virtual type *get_##name();
#define AST_CHILD_GETTER_DECL_OVERRIDE(type, name)  virtual type *get_##name() override;
#define AST_CHILD_GETTER_IMPL(type, name)           virtual type *get_##name()          {return AST_PROPERTY(name).get();}
#define AST_CHILD_GETTER_IMPL_OVERRIDE(type, name)  virtual type *get_##name() override {return AST_PROPERTY(name).get();}
#define AST_CHILD_DECL(type, name)                  AST_CHILD_GETTER_DECL(type, name);          AST_CHILD_SETTER_DECL(type, name);
#define AST_CHILD_DECL_OVERRIDE(type, name)         AST_CHILD_GETTER_DECL_OVERRIDE(type, name); AST_CHILD_SETTER_DECL_OVERRIDE(type, name);
#define AST_CHILD_IMPL(type, name)                  AST_CHILD_GETTER_IMPL(type, name);          AST_CHILD_SETTER_IMPL(type, name);
#define AST_CHILD_IMPL_OVERRIDE(type, name)         AST_CHILD_GETTER_IMPL_OVERRIDE(type, name); AST_CHILD_SETTER_IMPL_OVERRIDE(type, name);
#define AST_CHILD_DEFINE(type, name)                public: AST_CHILD_IMPL(type, name);          private: type::pointer_type AST_PROPERTY(name)
#define AST_CHILD_DEFINE_OVERRIDE(type, name)       public: AST_CHILD_IMPL_OVERRIDE(type, name); private: type::pointer_type AST_PROPERTY(name)



#define AST_FUNC_TRACE()    do {printf("%s\n", __func__);} while(0)



#define AST_IMPLEMENT_ABSTRACT(class__) \
public: \
    typedef j4a::ref_ptr<class__> pointer_type;

#define AST_IMPLEMENT(class__) \
public: \
    AST_IMPLEMENT_ABSTRACT(class__); \
private: \
    class __hide_parent_create {}; \
    static class__ *create(__hide_parent_create) {return NULL;}


#define AST_CREATE_NONAME___ABSTRACT(class__, super__) \
protected: \
    explicit class__(): super__() {;}

#define AST_CREATE_NONAME__(class__, super__) \
    AST_CREATE_NONAME___ABSTRACT(class__, super__); \
public: \
    static class__ *create() \
    { \
        class__ *obj = new class__(); \
        obj->put_in_pool(); \
        return obj; \
    }

#define AST_CREATE_NAMED____ABSTRACT(class__, super__) \
protected: \
    explicit class__(const j4a::string& name):  super__(name) {;} \

#define AST_CREATE_NAMED___(class__, super__) \
    AST_CREATE_NAMED____ABSTRACT(class__, super__); \
public: \
    static class__ *create(const j4a::string& name) \
    { \
        class__ *obj = new class__(name); \
        obj->put_in_pool(); \
        return obj; \
    }


#define AST_CREATE_POINTER__ABSTRACT(class__, super__, node__) \
protected: \
    explicit class__(node__ *rhs): super__(rhs) {;}

#define AST_CREATE_POINTER_(class__, super__, node__) \
    AST_CREATE_POINTER__ABSTRACT(class__, super__, node__); \
public: \
    static class__ *create(node__* rhs) \
    { \
        class__ *obj = new class__(rhs); \
        obj->put_in_pool(); \
        return obj; \
    }

#endif
