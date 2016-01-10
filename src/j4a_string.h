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

#ifndef J4A_STRING__H
#define J4A_STRING__H

#include "j4a__def.h"
#include <memory>
#include <string>
#include <sstream>

NS_J4A_BEGIN

class string_data;

class string
{
public:
    typedef std::string::size_type size_type;
    static const size_type npos = std::string::npos;

    ~string();
    string();
    string(const string& str);
    string(const char* str)                                         {assign(str);}
    string(const std::string& str)                                  {assign(str);}
    string(const std::ostringstream& str)                           {assign(str);}
    string(const string& str, size_type pos, size_type len = npos)  {assign(str, pos, len);}
    string(const char* s, size_type n)                              {assign(s, n);}
    string(size_type n, char c)                                     {assign(n, c);}
    template <class InputIterator>
    string(InputIterator first, InputIterator last)                 {assign(first, last);}

    string& operator=(const string& str)                {return assign(str);}
    string& operator=(const char* str)                  {return assign(str);}
    string& operator=(const std::string& str)           {return assign(str);}
    string& operator=(const std::ostringstream& str)    {return assign(str);}
    bool    operator<(const string &str) const;
    string& operator+=(const string& str)   {return append(str);}
    string& operator+=(const char* str)     {return append(str);}
    string& operator+=(const char str)      {return append(1, str);}

    string& assign(const string& str);
    string& assign(const char* str);
    string& assign(const std::string& str);
    string& assign(const std::ostringstream& str);
    string& assign(const string& str, size_type pos, size_type len = npos);
    string& assign(const char* s, size_type n);
    string& assign(size_type n, char c);
    template <class InputIterator>
    string& assign(InputIterator first, InputIterator last);

    string& append(const string& str);
    string& append(const string& str, size_type subpos, size_type sublen);
    string& append(const char* s);
    string& append(const char* s, size_type n);
    string& append(size_type n, char c);  
    template <class InputIterator>
    string& append(InputIterator first, InputIterator last);

    int compare(const string& str) const;
    int compare(size_type pos, size_type len, const string& str) const;
    int compare(size_type pos, size_type len, const string& str, size_type subpos, size_type sublen) const;
    int compare(const char* s) const;
    int compare(size_type pos, size_type len, const char* s) const;
    int compare(size_type pos, size_type len, const char* s, size_type n) const;


    bool               is_null() const;
    const std::string& std_str() const;
    const char*        c_str()   const   {return std_str().c_str();}

    string quoted(char quote_char = '"') const;

private:
    const std::shared_ptr<string_data>& shared_ptr_() const;
    std::shared_ptr<string_data>&       shared_ptr_();
    const std::string&                  shared_string_() const;
    std::string&                        shared_string_();

    // copy on write
    std::shared_ptr<string_data> m_data_shared_ptr;

    string& do_assign(const std::string& str);
};

inline string make_quoted(const string& text, char quote_char = '"')
{
    return text.quoted(quote_char);
}

inline string make_quoted(const char *text, char quote_char = '"')
{
    return string(text).quoted(quote_char);
}

NS_GLOBAL_BEGIN

inline bool operator<(const string &lhs, const string &rhs)
{
    if (lhs.is_null())
        return !rhs.is_null();

    if (rhs.is_null())
        return false;

    return lhs.std_str() < rhs.std_str();
}

inline string operator+(const string& lhs, const string& rhs) {string r(lhs); return r += rhs;}
inline string operator+(const string& lhs, const char*   rhs) {string r(lhs); return r += rhs;}
inline string operator+(const char*   lhs, const string& rhs) {string r(lhs); return r += rhs;}
inline string operator+(const string& lhs, char          rhs) {string r(lhs); return r += rhs;}
inline string operator+(char          lhs, const string& rhs) {string r(1, lhs); return r += rhs;}

inline std::ostream&
operator<<(std::ostream& os, const string& rhs) {return os << rhs.std_str();}

NS_GLOBAL_END

NS_J4A_END

#endif
