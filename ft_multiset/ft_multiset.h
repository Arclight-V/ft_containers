//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_MULTISET_H
#define FT_MULTISET_H

#include "stdafx.h"

namespace ft

template<class T, class Alloc = std::allocator<T> >
class multiset {

private:
    
public:
    /* common type definitions for all containers */
    typedef T                                               value_type;
    typedef Alloc                                           allocator_type;
    typedef typename allocator_type::reference              reference;
    typedef typename allocator_type::const_reference        const_reference;
    typedef typename allocator_type::pointer                pointer;
    typedef typename allocator_type::const_pointer          const_pointer;

    /*
     * define iterators
     *
     * typedef typename iterator;
     * typedef typename const_iterator;
     * typedef typename reverse_iterator:
     * typedef typename const_reverse_iterator;
     *
     */

    /* define difference_type
     * ...
     *
     */

    using size_type = size_t;
    using ref = reference;
    using c_ref = const_reference;
    using ptr = pointer;
    using c_ptr = const_pointer;
    /*
     * using
     * using it = iterator;
     * using c_it = const_iterator;
     * using rev_it = reverse_iterator;
     * using c_rev_it = const_reverse_iterator
     * using diff = difference_type;
     */

    /*
     * * * * * * * * * * * * * * * * * * * * * * * *
     * common member functions for all containers  *
     * * * * * * * * * * * * * * * * * * * * * * * *
    */

    /*
     *  empty container constructor (default constructor)
     *  Constructs an empty container, with no elements.
     *
     * explicit multiset (const allocator_type& alloc = allocator_type());
     *
     */
    /*
     *  copy constructor
     *  Constructs a container with a copy of each of the elements in x, in the same order.
     *
     * multiset (const multiset& x);
     */

    /*
     *  multiset destructor
     *  Destroys the container object.
     *
     * ~multiset();
     */

    /*
     * Return iterator to beginning
     * Returns an iterator pointing to the first element in the multiset container.
     *
     * it begin() {};
     * c_it begin() const {};
     */

    /*
     * Return iterator to end
     * Returns an iterator referring to the past-the-end element in the vector container.
     *
     * it end() {};
     * c_it end() const {};
     */

    /*
     * Return reverse iterator to reverse beginning
     * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
     *
     * rev_it rbegin();
     * c_rev_it rbegin() const;
     */

    /*
     * Return reverse iterator to reverse end
     * Returns a reverse iterator pointing to the theoretical element preceding the first element in the multiset container (which is considered its reverse end).
     *
     * rev_it rend();
     * c_rev_it rend() const;
     */

    /*
     * Relational operators
     *
     */
    /*
    template <class T, class Alloc>
    bool operator== (const multiset<T,Alloc>& lhs, const multiset<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator!= (const multiset<T,Alloc>& lhs, const multiset<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator<  (const multiset<T,Alloc>& lhs, const multiset<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator<= (const multiset<T,Alloc>& lhs, const multiset<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator>  (const multiset<T,Alloc>& lhs, const multiset<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator>= (const multiset<T,Alloc>& lhs, const multiset<T,Alloc>& rhs);
     *
     */

    /*
     * Capacity
     *
     * Test whether container is empty
     * Returns whether the multiset container is empty (i.e. whether its size is 0).
     *
     * bool empty() const;
     *
     * Return size
     * Returns the number of elements in the multiset container.
     *
     * size_type size() const;
     *
     * Return maximum size
     * Returns the maximum number of elements that the multiset container can hold.
     *
     * size_type max_size() const;
     *
     */

};


#endif //FT_MULTISET_H
