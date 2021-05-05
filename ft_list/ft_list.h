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
        T               value;
        s_node          *previous;
        s_node          *next;
    }                   t_node;
public:
    /* common type definitions for all containers */
    typedef T                                                       value_type;
    typedef Alloc                                                   allocator_type;
    typedef typename allocator_type::reference                      reference;
    typedef typename allocator_type::const_reference                const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;

    typedef typename ft::ListIterator<value_type>                   iterator;
    typedef typename ft::ListIterator<const value_type>             const_iterator;
    typedef typename ft::ListIterator<iterator>                     reverse_iterator:
    typedef typename ft::ListIterator<const_iterator>               const_reverse_iterator;

    typedef typename ft::ListIterator<value_type>::difference_type  difference_type;

    /*
     * alias
     */
    using size_type = size_t;
    using ref = reference;
    using c_ref = const_reference;
    using ptr = pointer;
    using c_ptr = const_pointer;
    using it = iterator;
    using c_it = const_iterator;
    using rev_it = reverse_iterator;
    using c_rev_it = const_reverse_iterator
    using diff = difference_type;

    /*
     * * * * * * * * * * * * * * * * * * * * * * * *
     * common member functions for all containers  *
     * * * * * * * * * * * * * * * * * * * * * * * *
    */

    //  empty container constructor (default constructor)
    //  Constructs an empty container, with no elements.
    explicit list (const allocator_type& alloc = allocator_type());


    /*
     *  copy constructor
     *  Constructs a container with a copy of each of the elements in x, in the same order.
     *
     * list (const list& x);
     */

    /*
     *  list destructor
     *  Destroys the container object.
     *
     * ~list();
     */

    /*
     * Return iterator to beginning
     * Returns an iterator pointing to the first element in the list container.
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
     * Returns a reverse iterator pointing to the theoretical element preceding the first element in the list container (which is considered its reverse end).
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
    bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

    template <class T, class Alloc>
    bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
     *
     */

    /*
     * Capacity
     *
     * Test whether container is empty
     * Returns whether the list container is empty (i.e. whether its size is 0).
     *
     * bool empty() const;
     *
     * Return size
     * Returns the number of elements in the list container.
     *
     * size_type size() const;
     *
     * Return maximum size
     * Returns the maximum number of elements that the list container can hold.
     *
     * size_type max_size() const;
     *
     */

    /*
     * * * * * * * * * * * * * * * * * * * * * * * * * *
     * common member functions for sequence containers *
     * * * * * * * * * * * * * * * * * * * * * * * * * *
    */

    /*
     * fill constructor
     * Constructs a container with n elements. Each element is a copy of val.
     *
     * explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
     */

    /*
     * range constructor
     * Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
     *
     * template<class InputIterator>
     * list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
    */

    /*
     * it insert (it position, const value_type& val);
     *
     * void insert (it position, size_type n, const value_type& val);
     *
     * template <class InputIterator>
     * void insert (it position, InputIterator first, InputIterator last); // first and last must not be iterators pointing to the inserted container
     */

    /*
     * Erase elements
     * Removes from the list container either a single element (position) or a range of elements ([first,last))
     *
     * it erase (iterator position);
     *
     * it erase (iterator first, iterator last);
     */

    /*
     * Clear content
     * Removes all elements from the list container (which are destroyed), and leaving the container with a size of 0.
     *
     * void clear();
     */






};


#endif //FT_LIST_H
