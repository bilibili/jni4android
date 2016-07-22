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

#ifndef J4A__DEF__H
#define J4A__DEF__H

// System Headers
#include <unistd.h>

// C Headers
#include <stdlib.h>
#include <stdio.h>

// C++ Headers
#include <memory>
#include <ostream>

#define NS_J4A_BEGIN namespace j4a {
#define NS_J4A_END   }

#define NS_GLOBAL_BEGIN  namespace global {
#define NS_GLOBAL_END    }

NS_J4A_BEGIN

class string;

class fill
{
public:
    fill(char ch, int width): m_ch(ch), m_width(width) {;}
    char m_ch;
    int  m_width;
};

NS_GLOBAL_BEGIN

template<class char_t, class traits_t>
inline std::basic_ostream<char_t, traits_t>&
operator<<(std::basic_ostream<char_t, traits_t>&            os,
           const std::auto_ptr<std::basic_string<char_t> >& str)
{
    return os << str->c_str();
}

template<class char_t, class traits_t>
inline std::basic_ostream<char_t, traits_t>&
operator<<(std::basic_ostream<char_t, traits_t>& os, const j4a::fill& rhs)
{
    for (int i = 0; i < rhs.m_width; ++i)
        os << rhs.m_ch;
    return os;
}

NS_GLOBAL_END

NS_J4A_END

using namespace j4a::global;

#endif
