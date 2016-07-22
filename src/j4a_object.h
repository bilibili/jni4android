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

#ifndef J4A__OBJECT__H
#define J4A__OBJECT__H

#include <assert.h>
#include "j4a__def.h"
#include "j4a_ref_ptr.h"

NS_J4A_BEGIN

class object
{
public:
    int add_ref() const
    {
        return __sync_add_and_fetch(&m_ref_count, 1);
    }

    int release() const
    {
        int ref_count = __sync_sub_and_fetch(&m_ref_count, 1);
        assert(ref_count >= 0);
        if (ref_count == 0)
            delete this;
        return ref_count;
    }

    int _get_ref() const {return m_ref_count;}

private:
    volatile mutable int m_ref_count;

protected:
    object(): m_ref_count(0) {;}
    virtual ~object() {;}

private:
    object(const object&);
    object &operator=(const object&);
};

typedef ref_ptr<object> object_ptr;

NS_J4A_END

#endif
