//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_LIST_H
#define FT_LIST_H

//#include "stdafx.h"
#include "listIterator.h"
#include "NodeTraits.h"

namespace ft {

    template<typename T, typename Alloc = std::allocator<T> >
    class list {
        typedef typename ft::NodeTraits<T>::_dl_list_TS node;
        node *_tail;   //  using the tail has access to the head
    public:
        /* common type definitions for all containers */
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;

        typedef typename ft::ListIterator<value_type>                   iterator;
        typedef typename ft::ListConstIterator<value_type, T const *>   const_iterator;
        typedef typename ft::ListIterator<iterator>                     reverse_iterator;
        typedef typename ft::ListIterator<const_iterator>               const_reverse_iterator;

        typedef typename ft::ListIterator<value_type, t_node>::difference_type  difference_type;

        typedef size_t size_type;

        /*
         * * * * * * * * * * * * * * * * * * * * * * * *
         * Common Member Functions For All Containers  *
         * * * * * * * * * * * * * * * * * * * * * * * *
        */
        //      Empty container constructor (default constructor)
        //      Constructs an empty container, with no elements.
        explicit list(const allocator_type &alloc = allocator_type()) : _tail(allocateMemoryForNode()), _alloc(alloc),
                                                                        _size(0) {};


        //     Copy constructor
        //     Constructs a container with a copy of each of the elements in x, in the same order.
        /*
        list (const list& x) {

        };
         */

        /*
         *  list destructor
         *  Destroys the container object.
         */
        virtual ~list() {};

        /*
         *  Return iterator to beginning
         *  Returns an iterator pointing to the first element in the list container.
         */
        iterator begin() {
            return iterator(_tail->next);
        };

        const_iterator begin() const {
            return const_iterator(_tail->next);
        };

        /*
         *  Return iterator to end
         *  Returns an iterator referring to the past-the-end element in the list container.
         */
        iterator end() {
            return iterator(_tail);
        }

        const_iterator end() const {
            return const_iterator(_tail);
        }

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

        /*
         * Add element at the end
         * Adds a new element at the end of the list container, after its current last element.
         * The content of val is copied (or moved) to the new element.
         */
//        void push_back(value_type const &val) {
//            insert(end(), val);
//            iterator itEnd = end();
//
//        }
//
        /*
         *  Insert elements
         *  The container is extended by inserting new elements before the element at the specified position.
         */
        iterator insert(iterator position, value_type const &val) {
            node *NewNode = nullptr;

            allocateMemoryForNodeAndConstruct(val, &NewNode);
            exchangeOfpointersBetweenNodes(NewNode, position._node);
            return iterator(NewNode);
        }

        void insert(iterator position, size_type n, value_type const &val)
        {
            for (size_type i = 0; i < n ; ++i) {
                insert(position, val);
            }
        }

    private:
        allocator_type _alloc;
        std::allocator<node> _allocNode;
        size_type _size;

        node *allocateMemoryForNode() {
            node *newNode = _allocNode.allocate(1);
            std::memset(&newNode->value_type, 0, sizeof(value_type));
            newNode->previous = newNode;
            newNode->next = newNode;
            return newNode;
        }

        void allocateMemoryForNodeAndConstruct(value_type const &val, node **node) {
            *node = allocateMemoryForNode();
            _alloc.construct(&(*node)->value_type, val);
        }

        void exchangeOfpointersBetweenNodes(node *&node1, node *&node2) {
            node1->next = node2;
            node1->previous = node2->previous;
            node2->previous->next = node1;
            node2->previous = node1;
        }
    };


}


#endif //FT_LIST_H
