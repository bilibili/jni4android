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

#ifndef J4A_STRING_POOL__H
#define J4A_STRING_POOL__H

#include "j4a_string.h"
#include <set>

NS_J4A_BEGIN

class string_pool
{
public:
    typedef std::set<string> pool;

    static string_pool &instance();
    const string& obtain_string_ref(const char *text);
    const string* obtain_string_ptr(const char *text);

private:
    string_pool() {;}

    pool m_pool;
};

inline const string* make_managed_str_ptr(const char *text)
{
    return string_pool::instance().obtain_string_ptr(text);
}

NS_J4A_END

#endif
