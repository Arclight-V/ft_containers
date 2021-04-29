//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_LIST_H
#define FT_LIST_H

#include "stdafx.h"

namespace ft

template<class T, class Alloc = std::allocator<T> >
class list {

private:
    typedef struct      s_node
    {
        T               *data;
        s_node          *previous;
        s_node          *next;
    }                   t_node;
public:
    typedef T                                               value_type;
    typedef Alloc                                           allocator_type;

    typedef typename allocator_type::reference              reference;
    typedef typename allocator_type::const_reference        const_reference;
    typedef typename allocator_type::pointer                pointer;
    typedef typename allocator_type::const_pointer          const_pointer;

    /*
     * define iterators
     */

    using size_type = size_t;
    using ref = reference;
    using c_ref = const_reference;
    using ptr = pointer;
    using c_ptr = const_pointer;

    ft_list();
};


#endif //FT_LIST_H
