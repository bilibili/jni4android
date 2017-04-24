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

#ifndef J4A_AST__FORWARD__H
#define J4A_AST__FORWARD__H

#include <cassert>
#include "j4a_string.h"
#include "j4a_object.h"
#include "j4a_ref_ptr.h"

#define NS_AST_BEGIN namespace ast {
#define NS_AST_END   }

NS_AST_BEGIN

// https://docs.oracle.com/javase/specs/jls/se7/html/jls-18.html
class Annotation;
class Annotations;
class Argument;
class ArgumentList;
class Class;
class ClassIdentifier;
class CompilationUnit;
class Constructor;
class Field;
class Identifier;
class ImportList;
class MemberList;
class Method;
class MethodList;
class ModifierSet;
class Node;
class PrimitiveType;
class ReferenceType;
class Type;

NS_AST_END

#endif
