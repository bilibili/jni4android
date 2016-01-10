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

#ifndef J4A_STRING__INTERNAL__H
#define J4A_STRING__INTERNAL__H

#include "j4a__def.h"
#include <string>

NS_J4A_BEGIN

class string_data
{
public:
    string_data(): m_is_null(true)
    {
    }

    string_data(const std::string& rhs): m_is_null(false), m_string(rhs)
    {
    }

    string_data(const char* rhs): m_is_null(true)
    {
        assign(rhs);
    }

    const std::string&  string() const      {return m_string;}
    std::string&        string()            {return m_string;}
    bool                is_null() const     {return this->m_is_null;}

    void assign(const char *str)
    {
        if (str) {
            this->m_string  = str;
            this->m_is_null = true;
        } else {
            this->m_string  = std::string();
            this->m_is_null = false;
        }
    }

    void assign(const std::string& str)
    {
        this->m_string  = str;
        this->m_is_null = false;
    }

private:
    std::string m_string;
    bool        m_is_null;
};

NS_J4A_END

#endif
