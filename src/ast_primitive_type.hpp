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

#ifndef J4A__AST_PRIMITIVE_TYPE__HPP
#define J4A__AST_PRIMITIVE_TYPE__HPP

#include "ast__def.hpp"
#include "ast_type.hpp"

NS_AST_BEGIN

class PrimitiveType: public Type
{
public:
    AST_IMPLEMENT_ABSTRACT(PrimitiveType);
protected:
    explicit PrimitiveType(const j4a::string& name, int token): Type(name), m_token(token) {;}

public:
    // @Override
    virtual bool is_reference_type() override {return get_is_array();}
    virtual bool is_void_type() override {return m_token == T_VOID;}
    virtual bool is_string_type() override {return false;}

private:
    const int m_token;
};

#define AST_DEFINE__PrimitiveType(class__, token_id__, name__, ctype__, c_sign__, c_name_in_call_api, default__) \
class class__: public PrimitiveType \
{ \
public: \
    AST_IMPLEMENT(class__); \
private: \
    explicit class__(): PrimitiveType(name__, token_id__) {;} \
public: \
    static class__ *create() \
    { \
        pointer_type instance = new class__(); \
        instance->put_in_pool(); \
        return instance; \
    } \
public: \
    virtual j4a::string get_c_type() override { \
        if (get_is_array()) \
            return ctype__ "Array"; \
        else \
            return ctype__; \
    } \
    virtual j4a::string get_c_sign_in_method() override { \
        if (get_is_array()) { \
            std::ostringstream os; \
            os << "[" << c_sign__; \
            return os; \
        } else \
            return c_sign__; \
    } \
    virtual j4a::string get_c_default_value() override { \
        if (get_is_array()) { \
            return "NULL"; \
        } else \
            return default__; \
    } \
    virtual j4a::string get_c_call_instance_method_api() override { \
        std::ostringstream os; \
        os << "Call" << (get_is_array() ? "Object" : c_name_in_call_api) << "Method"; \
        return os; \
    } \
    virtual j4a::string get_c_call_static_method_api() override { \
        std::ostringstream os; \
        os << "CallStatic" << (get_is_array() ? "Object" : c_name_in_call_api) << "Method"; \
        return os; \
    } \
    virtual j4a::string get_c_get_instance_field_api() override { \
        std::ostringstream os; \
        os << "Get" << (get_is_array() ? "Object" : c_name_in_call_api) << "Field"; \
        return os; \
    } \
    virtual j4a::string get_c_get_static_field_api() override { \
        std::ostringstream os; \
        os << "GetStatic" << (get_is_array() ? "Object" : c_name_in_call_api) << "Field"; \
        return os; \
    } \
    virtual j4a::string get_c_set_instance_field_api() override { \
        std::ostringstream os; \
        os << "Set" << (get_is_array() ? "Object" : c_name_in_call_api) << "Field"; \
        return os; \
    } \
    virtual j4a::string get_c_set_static_field_api() override { \
        std::ostringstream os; \
        os << "SetStatic" << (get_is_array() ? "Object" : c_name_in_call_api) << "Field"; \
        return os; \
    } \
};

AST_DEFINE__PrimitiveType(BooleanType,  T_BOOLEAN,  "boolean",  "jboolean", "Z", "Boolean", "false");
AST_DEFINE__PrimitiveType(ByteType,     T_BYTE,     "byte",     "jbyte",    "B", "Byte",    "0");
AST_DEFINE__PrimitiveType(FloatType,    T_FLOAT,    "float",    "jfloat",   "F", "Float",   "0");
AST_DEFINE__PrimitiveType(DoubleType,   T_DOUBLE,   "double",   "jdouble",  "D", "Double",  "0");
AST_DEFINE__PrimitiveType(CharType,     T_CHAR,     "char",     "jchar",    "C", "Char",    "0");
AST_DEFINE__PrimitiveType(ShortType,    T_SHORT,    "short",    "jshort",   "S", "Short",   "0");
AST_DEFINE__PrimitiveType(IntType,      T_INT,      "int",      "jint",     "I", "Int",     "0");
AST_DEFINE__PrimitiveType(LongType,     T_LONG,     "long",     "jlong",    "J", "Long",    "0");
AST_DEFINE__PrimitiveType(VoidType,     T_VOID,     "void",     "void",     "V", "Void",    "");

NS_AST_END

#endif
