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

#ifndef J4A__AST_ANNOTATION__HPP
#define J4A__AST_ANNOTATION__HPP

#include "ast__def.hpp"
#include "ast_identifier.hpp"

NS_AST_BEGIN

class Annotation: public Identifier
{
public:
    AST_IMPLEMENT(Annotation);
    AST_CREATE_NAMED___(Annotation, Identifier);

    AST_PROPERTY_DEFINE(j4a::string, value);

public:
    // @Override
    virtual void debug_print(int indent) override {
        if (get_value().is_null())
            std::cout << "@" << get_name() << std::endl;
        else
            std::cout << "@" << get_name() << "(" << get_value() << ")" << std::endl;
    }
};

class Annotations: public IdentifierMap<Annotation>
{
public:
    AST_IMPLEMENT(Annotations);
    AST_CREATE_NONAME__(Annotations, IdentifierMap<Annotation>);

public:
    // @Override
    virtual void debug_print(int indent) override {
        iterator begin = this->begin();
        iterator end   = this->end();

        for (NULL; begin != end; ++begin) {
            begin->second->debug_print(indent);
        }
    }
};

NS_AST_END

#endif
