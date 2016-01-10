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

#ifndef J4A__AST_IMPORT__HPP
#define J4A__AST_IMPORT__HPP

#include "ast__def.hpp"
#include "ast_node.hpp"
#include "ast_identifier.hpp"

NS_AST_BEGIN

class ImportList: public NodeList<Identifier>
{
public:
    AST_IMPLEMENT(ImportList);
    AST_CREATE_NONAME__(ImportList, NodeList<Identifier>);

public:
    // @Override
    virtual void debug_print(int indent) override {
        if (size() > 0) {
            printf("\n");

            iterator begin = this->begin();
            iterator end   = this->end();

            for (NULL; begin != end; ++begin) {
                printf("import ");
                (*begin)->debug_print(indent);
                printf(";\n");
            }
        }
    }
};

NS_AST_END

#endif
