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

#ifndef J4A__AST_ARGUMENT__HPP
#define J4A__AST_ARGUMENT__HPP

#include "ast__def.hpp"
#include "ast_type.hpp"

NS_AST_BEGIN

class Argument: public Identifier
{
public:
    AST_IMPLEMENT(Argument);
    AST_CREATE_NAMED___(Argument, Identifier);

    AST_CHILD_DEFINE(Type, type);

public:
    // @Override
    virtual void debug_print(int indent) override {
        get_type()->debug_print(0);
        std::cout << " " << get_name();
    }
};

class ArgumentList: public NodeList<Argument>
{
public:
    AST_IMPLEMENT(ArgumentList);
    AST_CREATE_NONAME__(ArgumentList, NodeList<Argument>);

    // @Override
    virtual void debug_print(int indent) override {
        iterator begin = this->begin();
        iterator end   = this->end();

        if (begin != end) {
            (*begin)->debug_print(indent);
            ++begin;

            for (NULL; begin != end; ++begin) {
                printf(", ");
                (*begin)->debug_print(indent);
            }
        }
    }
};

NS_AST_END

#endif
