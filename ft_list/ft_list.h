//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_LIST_H
#define FT_LIST_H

//#include "stdafx.h"
#include "listIterator.h"
#include "NodeTraits.h"
#include "ReverseIterator.h"
#include "Algorithm.h"
#include "utils.h"

namespace ft {
    template<typename T, typename Alloc = std::allocator<T> >
    class list {
        typedef typename ft::NodeTraits<T>::_dl_list_TS node;
        node *_tail;   //  using the tail has access to the head
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;

        typedef typename ft::ListIterator<value_type>                   iterator;
        typedef typename ft::ListConstIterator<value_type, T const *>   const_iterator;
        typedef typename ft::ReverseIterator<iterator>                     reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator>               const_reverse_iterator;

        typedef typename ft::ListIterator<value_type>::difference_type  difference_type;

        typedef size_t size_type;


        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        // Empty container constructor (default constructor)
        // Constructs an empty container, with no elements.

        explicit list(const allocator_type &alloc = allocator_type()) : _tail(allocateMemoryForNode()),
                                                                        _alloc(alloc),
                                                                        _size(0) {}

        //  Fill constructor
        //  Constructs a container with n elements. Each element is a copy of val.

         explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _tail(allocateMemoryForNode()),
                                                                                                                             _alloc(alloc),
                                                                                                                             _size(0) {
            for (size_type i = 0; i < n ; ++i) {
                push_back(val);
            }
         }

         // Range constructor
         // Constructs a container with as many elements as the range [first,last), with each element constructed from
         // its corresponding element in that range, in the same order.

         template<class InputIterator>
         list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) :_tail(allocateMemoryForNode()),
                                                                                                        _alloc(alloc),
                                                                                                        _size(0) {
             for (; first != last; ++first) {
                 push_back(*first);
             }
         }

        //  Copy constructor
        //  Constructs a container with a copy of each of the elements in x, in the same order.

        list (const list& x) : _tail(allocateMemoryForNode()),
                               _alloc(x.get_allocator()),
                               _size(0) {
            for (const_iterator itBegin = x.begin(), itEnd = x.end(); itBegin != itEnd; ++itBegin) {
                push_back(*itBegin);
            }
        };

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------

        virtual ~list() {
            clear();
            destroyAndDeallocateNode(_tail);
        }

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        list &operator=(const list& x) {
            if (this != &x) {
                clear();
                for (const_iterator itBegin = x.begin(), itEnd = x.end(); itBegin != itEnd; ++itBegin) {
                    push_back(*itBegin);
                }
            }
        }

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

        reverse_iterator  rbegin() {
            return reverse_iterator(_tail);
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(_tail);
        }

        reverse_iterator rend() {
            return reverse_iterator(_tail->next);
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(_tail->next);
        }


        // -----------------------------------------CAPACITY------------------------------------------------------------

        bool empty() const {
            return _size == 0;
        }

        size_type size() const {
            return _size;
        };

         size_type max_size() const {
             return _alloc.max_size();
         };

        // -----------------------------------------ELEMENT ACCESS------------------------------------------------------

        reference front() {
            return _tail->next->value_type;
        }

        const_reference front() const {
            return _tail->next->value_type;
        }

        reference back() {
            return _tail->value_type;
        }

        const_reference back() const {
            return _tail->value_type;
        }

        // -----------------------------------------MODIFIERS-----------------------------------------------------------

        // -----------------------------------------Assign new content to container-------------------------------------

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last, typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) {
            (void)isIter;
            clear();
            for(;first != last; ++first) {
                push_back(*first);
            }
        }

        // -----------------------------------------Assign new content to container-------------------------------------

        void assign(size_type n, const value_type& val) {
            clear();
            for(;n; --n) {
                push_back(val);
            }
        }

        // -----------------------------------------Insert Element At Beginning-----------------------------------------

        void push_front (const value_type& val) {
            node *NewNode = nullptr;
            executeInsert(&NewNode, &_tail, val);
        }

        // -----------------------------------------Delete first element------------------------------------------------

        void pop_front() {
             node *retNode = _tail->next;
             exchangeOfpointersBetweenNodes(&_tail->previous, &_tail->next);
             destroyAndDeallocateNode(_tail->next);
             --_size;
        }

        // -----------------------------------------Add Element At The End----------------------------------------------

        void push_back(value_type const &val) {
            node *NewNode = nullptr;
            allocateMemoryForNodeAndConstruct(val, &NewNode);
            exchangeOfpointersBetweenNodes(&NewNode, &_tail);
            ++_size;
        }

        // -----------------------------------------Delete last element-------------------------------------------------

        void pop_back() {
            node *toDeleted = _tail->previous;
            _tail->previous->previous->next = _tail;
            _tail->previous = _tail->previous->previous;
            destroyAndDeallocateNode(toDeleted);
            --_size;
        }

        // -----------------------------------------Insert Elements-----------------------------------------------------

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
             position._node->previous->next = position._node->next;
             position._node->next->previous = position._node->previous;
             node *retNode = position._node->next;
             destroyAndDeallocateNode(position._node);
             --_size;
             return iterator(retNode);
         }

         iterator erase(iterator first, iterator last) {
            first._node->previous->next = last._node;
            last._node->previous = first._node->previous;
             for (; first != last; ++first) {
                 destroyAndDeallocateNode(first._node);
                 --_size;
             }
             return last;
        }

        // -----------------------------------------Swap Content--------------------------------------------------------

        void swap (list& x) {
            ft::swap(_tail, x._tail);
            ft::swap(_alloc,x._alloc);
            ft::swap(_allocNode, x._allocNode);
            ft::swap(_size,x._size);
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

        // -----------------------------------------OBSERVERS-----------------------------------------------------------

        allocator_type get_allocator() const {
            return _alloc;
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

        /*
        ** -----------------------------------------NON-MEMBER FUNCTIONS------------------------------------------------
        */

        // -----------------------------------------Relational Operators------------------------------------------------

        template <class T, class Alloc>
        bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
            return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        template <class T, class Alloc>
        bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
            return !(lhs == rhs);
        }

        template <class T, class Alloc>
        bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        template <class T, class Alloc>
        bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
            return !(rhs < lhs);
        }

        template <class T, class Alloc>
        bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
            return lhs < rhs;
        }

        template <class T, class Alloc>
        bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
            return !(lhs < rhs);
        }

        // -----------------------------------------Swap----------------------------------------------------------------

        template <class T, class Alloc>
        void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
            x.swap(y);
        }

}


#endif //FT_LIST_H
