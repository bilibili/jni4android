/*
 * copyright (c) 2016 Zhang Rui <bbcallen@gmail.com>
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

#include "j4a_string.h"
#include "j4a_string.internal.h"
#include <string>

using namespace j4a;

const std::shared_ptr<string_data>& string::shared_ptr_() const
{
    return m_data_shared_ptr;
}

std::shared_ptr<string_data>& string::shared_ptr_()
{
    if (!m_data_shared_ptr.unique())
        m_data_shared_ptr.reset(new string_data(*m_data_shared_ptr));

    return m_data_shared_ptr;
}

const std::string& string::shared_string_() const
{
    return shared_ptr_()->string();
}

std::string& string::shared_string_()
{
    return shared_ptr_()->string();
}

string::~string()
{

}

string::string(): m_data_shared_ptr(new string_data())
{
}

string::string(const string& str): m_data_shared_ptr(str.m_data_shared_ptr)
{    
}

string& string::assign(const string& str)
{
    m_data_shared_ptr = str.m_data_shared_ptr;
    return *this;
}

string& string::assign(const char* str)
{
    if (m_data_shared_ptr.unique()) {
        m_data_shared_ptr->assign(str);
    } else {
        m_data_shared_ptr.reset(new string_data(str));        
    }

    return *this;
}

string& string::do_assign(const std::string& str)
{
    if (m_data_shared_ptr.unique()) {
        m_data_shared_ptr->assign(str.c_str());
    } else {
        m_data_shared_ptr.reset(new string_data(str));        
    }

    return *this;
}

string& string::assign(const std::string& str)
{
    return do_assign(str);
}

string& string::assign(const std::ostringstream& str)
{
    return do_assign(str.str());
}

string& string::assign(const string& str, size_type pos, size_type len)
{
    return do_assign(std::string(str.shared_string_(), pos, npos));
}

string& string::assign(const char* s, size_type n)
{
    return do_assign(std::string(s, n));
}

string& string::assign(size_type n, char c)
{
    return do_assign(std::string(n, c));
}

template <class InputIterator>
string& string::assign(InputIterator first, InputIterator last)
{
    return do_assign(std::string(first, last));
}

string& string::append(const string& str)
{
    shared_string_().append(str.shared_string_());
    return *this;
}

string& string::append(const string& str, size_type subpos, size_type sublen)
{
    shared_string_().append(str.shared_string_(), subpos, sublen);
    return *this;
}

string& string::append(const char* s)
{
    shared_string_().append(s);
    return *this;
}

string& string::append(const char* s, size_type n)
{
    shared_string_().append(s, n);
    return *this;
}

string& string::append(size_type n, char c)
{
    shared_string_().append(n, c);
    return *this;
}

template <class InputIterator>
string& string::append(InputIterator first, InputIterator last)
{
    shared_string_().append(first, last);
    return *this;
}

int string::compare(const string& str) const
{
    return shared_string_().compare(str.shared_string_());
}

int string::compare(size_type pos, size_type len, const string& str) const
{
    return shared_string_().compare(pos, len, str.shared_string_());
}

int string::compare(size_type pos, size_type len, const string& str, size_type subpos, size_type sublen) const
{
    return shared_string_().compare(pos, len, str.shared_string_(), subpos, sublen);
}

int string::compare(const char* s) const
{
    return shared_string_().compare(s);
}

int string::compare(size_type pos, size_type len, const char* s) const
{
    return shared_string_().compare(pos, len, s);
}

int string::compare(size_type pos, size_type len, const char* s, size_type n) const
{
    return shared_string_().compare(pos, len, s, n);
}

bool string::operator<(const string &rhs) const
{
    return shared_string_() < rhs.shared_string_();
}

bool string::is_null() const
{
    return shared_ptr_()->is_null();
}

const std::string& string::std_str() const
{
    return shared_string_();
}

string string::quoted(char quote_char) const
{
    std::string quoted;
    quoted.reserve(shared_string_().length() + 2);
    quoted.append(1, quote_char);
    quoted.append(shared_string_());
    quoted.append(1, quote_char);
    return quoted;
}
