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

        typedef typename ft::ListIterator<value_type>::difference_type  difference_type;

        typedef size_t size_type;

        /*
         * * * * * * * * * * * * * * * * * * * * * * * *
         * Common Member Functions For All Containers  *
         * * * * * * * * * * * * * * * * * * * * * * * *
        */

        /*
        ** -----------------------------------------CONSTRUCTOR---------------------------------------------------------
        */

        // Empty container constructor (default constructor)
        // Constructs an empty container, with no elements.

        explicit list(const allocator_type &alloc = allocator_type()) : _tail(allocateMemoryForNode()), _alloc(alloc),
                                                                        _size(0) {};

        //  fill constructor
        //  Constructs a container with n elements. Each element is a copy of val.

         explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {

         }


        //     Copy constructor
        //     Constructs a container with a copy of each of the elements in x, in the same order.
        /*
        list (const list& x) {

        };
         */

        /*
        ** -----------------------------------------DESTRUCTOR----------------------------------------------------------
        */

        virtual ~list() {
            clear();
            destroyAndDeallocateNode(_tail);
        }

        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */

        // -----------------------------------------ITERATORS-----------------------------------------------------------

        iterator begin() {
            return iterator(_tail->next);
        };

        const_iterator begin() const {
            return const_iterator(_tail->next);
        };

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
        ** -----------------------------------------CAPACITY------------------------------------------------------------
        */

        bool empty() const {
            return _size == 0;
        }

        size_type size() const {
            return _size;
        };

         size_type max_size() const {
             return _alloc.max_size();
         };

        /*
         * * * * * * * * * * * * * * * * * * * * * * * * * *
         * common member functions for sequence containers *
         * * * * * * * * * * * * * * * * * * * * * * * * * *
        */

        /*
         * range constructor
         * Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
         *
         * template<class InputIterator>
         * list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
        */

        // -----------------------------------------MODIFIERS-----------------------------------------------------------

        // -----------------------------------------Insert elements-----------------------------------------------------

        iterator insert(iterator position, value_type const &val) {
            node *NewNode = nullptr;
            executeInsert(&NewNode, &position._node, val);
            return iterator(NewNode);
        }

        void insert(iterator position, size_type n, value_type const &val)
        {
            for (size_type i = 0; i < n ; ++i) {
                node *NewNode = nullptr;
                executeInsert(&NewNode, &position._node, val);
            }
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
            for (; first != last; ++first) {
                node *NewNode = nullptr;
                executeInsert(&NewNode, &position._node, *first);
                ++position;
            }
        }

        // -----------------------------------------Erase Elements------------------------------------------------------

         iterator erase(iterator position) {
             node *retNode = position._node->next;

             exchangeOfpointersBetweenNodes(&position._node->previous, &position._node->next);
             destroyAndDeallocateNode(position._node);
             --_size;
             return iterator(retNode);
         }

         iterator erase(iterator first, iterator last) {
            node *saveNode = first._node->previous;

             for (; first != last; ++first) {
                 destroyAndDeallocateNode(first._node);
                 --_size;
             }
             exchangeOfpointersBetweenNodes(&saveNode, &first._node->next);
             return last;
        }

        // -----------------------------------------Push Elements-------------------------------------------------------

        void push_back(value_type const &val) {
            node *NewNode = nullptr;
            allocateMemoryForNodeAndConstruct(val, &NewNode);
            exchangeOfpointersBetweenNodes(&NewNode, &_tail);
            ++_size;
        }

        // -----------------------------------------Clear Content-------------------------------------------------------

        void clear() {
            node *nextNode = nullptr, *toDeleted = _tail->next;

            for (; _size != 0; --_size) {
                nextNode = toDeleted->next;
                destroyAndDeallocateNode(toDeleted);
                toDeleted = nextNode;
            }
            _tail->previous = _tail;
            _tail->next = _tail;
        }

    private:
        allocator_type _alloc;
        std::allocator<node> _allocNode;
        size_type _size;

        /*
        ** -----------------------------------------AUXILIARY FUNCTIONS-------------------------------------------------
        */

        // -----------------------------------------Allocate Memory-----------------------------------------------------

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

        // -----------------------------------------Deallocate Memory---------------------------------------------------

        void destroyAndDeallocateNode(node *node) {
            _alloc.destroy(&node->value_type);
            _allocNode.deallocate(node, 1);
        }

        // -----------------------------------------Exchange Of Pointers------------------------------------------------

        void exchangeOfpointersBetweenNodes(node **node1, node **node2) {
            (*node1)->next = *node2;
            (*node1)->previous = (*node2)->previous;
            (*node2)->previous->next = *node1;
            (*node2)->previous = *node1;
        }

        // -----------------------------------------Insert Element------------------------------------------------------

        void executeInsert(node **newNode, node **positionNode, value_type const &val) {
            allocateMemoryForNodeAndConstruct(val, newNode);
            exchangeOfpointersBetweenNodes(newNode, positionNode);
            ++_size;
        }
    };


}


#endif //FT_LIST_H
