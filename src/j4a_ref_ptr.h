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

#ifndef J4A__REF_PTR__H
#define J4A__REF_PTR__H

#include "j4a__def.h"

NS_J4A_BEGIN

template<class T>
class ref_ptr
{
public:
    typedef T           element_type;
    typedef ref_ptr<T>  my_type;

    void release()
    {
        if (m_p) {
            m_p->release();
            m_p = NULL;
        }
    }

    void assign(T* p)                   {do_assign(p);}
    void assign(const my_type &p)       {do_assign(p.m_p);}
    template <class T1>
    void assign(T1*& p)                 {do_assign(static_cast<T*>(p));}
    template <class T1>
    void assign(const ref_ptr<T1>& r)   {do_assign(static_cast<T*>(r.get()));}

    T*   get()      const {return static_cast<T*>(m_p);}
    T*   detach()         {T *p = m_p; m_p = NULL; return p;}
    bool is_null()  const {return !m_p;}

    T* operator->() const {return m_p;}
    T& operator*()  const {return *m_p;}
    operator bool() const {return !!m_p;}
    operator T*()   const {return m_p;}

private:
    void do_assign(T* p)
    {
        if (m_p == p)
            return;

        if (p)
            p->add_ref();

        release();
        m_p = p;
    }

public:
    ref_ptr(): m_p(NULL)        {;}
    ref_ptr(T* p): m_p(NULL)    {assign(p);}
    ~ref_ptr()                  {release();}

    ref_ptr(const my_type& r): m_p(NULL)    {assign(r);}
    my_type& operator=(const my_type& r)    {assign(r); return *this;}

    template <class T1>
    ref_ptr(T1* p): m_p(NULL)               {assign(p);}
    template <class T1>
    my_type& operator=(T1* p)               {assign(p); return *this;}

    template <class T1>
    ref_ptr(const ref_ptr<T1>& r): m_p(NULL) {assign(r);}
    template <class T1>
    my_type& operator=(const ref_ptr<T1>& r) {assign(r); return *this;}

private:
    mutable T *m_p;
};

NS_J4A_END

#endif
