//
// Created by Arclight Natashia on 6/10/21.
//

#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include "../common_templates/stdafx.h"
#include "../common_templates/NodeTraits.h"
#include "vectorIterator.h"
#include "../common_templates/ReverseIterator.h"
#include "../common_templates/Algorithm.h"
#include "../common_templates/utils.h"

namespace ft {
    template < class T, class Alloc = allocator<T> >
    class vector {
        typedef typename ft::NodeTraits<T>::_dl_list_TS node;

    public:
        typedef T                                                                   value_type;
        typedef Alloc                                                               allocator_type;
        typedef typename allocator_type::reference                                  reference;
        typedef typename allocator_type::const_reference                            const_reference;
        typedef typename allocator_type::pointer                                    pointer;
        typedef typename allocator_type::const_pointer                              const_pointer;

        typedef typename ft::VectorIterator<value_type, value_type *>               iterator;
        typedef typename ft::VectorConstIterator<value_type, value_type const *>    const_iterator;
        typedef typename ft::ReverseIterator<iterator>                              reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator>                        const_reverse_iterator;
        typedef typename ft::VectorIterator<value_type>::difference_type            difference_type;
        typedef size_t                                                              size_type;

    private:
        allocator_type                                                              _alloc;
        std::allocator<node>                                                        _allocNode;
        size_type                                                                   _size;

    public:
        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        // Empty container constructor (default constructor)
        // Constructs an empty container, with no elements.

        explicit vector (const allocator_type& alloc = allocator_type()) {

        }

        //  Fill constructor
        //  Constructs a container with n elements. Each element is a copy of val.

        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type()) {

        }

        // Range constructor
        // Constructs a container with as many elements as the range [first,last), with each element constructed from
        // its corresponding element in that range, in the same order.

        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type(), typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) {

        }

        //  Copy constructor
        //  Constructs a container with a copy of each of the elements in x, in the same order.

        vector (const vector& x) {

        }

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------

        virtual ~vector() {
            clear();
        }

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        vector &operator=(const vector& x) {
            if (this != &x) {
                clear();
                for (const_iterator itBegin = x.begin(), itEnd = x.end(); itBegin != itEnd; ++itBegin) {
                    push_back(*itBegin);
                }
            }
            return *this;
        }
/*
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
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
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
            return _tail->previous->value_type;
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
            node *newNode = nullptr;
            allocateMemoryForNodeAndConstruct(val, &newNode);
            _tail->next->previous = newNode;
            newNode->next = _tail->next;
            newNode->previous = _tail;
            _tail->next = newNode;
            ++_size;
        }

        // -----------------------------------------Delete first element------------------------------------------------

        void pop_front() {
            node *toDelete = _tail->next;

            unlinkNode(&_tail->next);
            destroyAndDeallocateNode(toDelete);
            --_size;
        }

        // -----------------------------------------Add Element At The End----------------------------------------------

        void push_back(value_type const &val) {
            node *NewNode = nullptr;
            allocateMemoryForNodeAndConstruct(val, &NewNode);
            insertingNodeBefore(&NewNode, &_tail);
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
        void insert(iterator position,
                    InputIterator first,
                    InputIterator last,
                    typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) {
            (void)isIter;
            node *tmp = position._node;
            for (; first != last; ++first) {
                node *NewNode = nullptr;
                executeInsert(&NewNode, &tmp, *first);
                tmp = NewNode->next;
            }
        }

        // -----------------------------------------Erase Elements------------------------------------------------------

        iterator erase(iterator position) {
            unlinkNodes(&position._node, &position._node);
            node *retNode = position._node->next;
            destroyAndDeallocateNode(position._node);
            --_size;
            return iterator(retNode);
        }

        iterator erase(iterator first, iterator last) {
            unlinkNodes(&first._node, &last._node->previous);
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

        // -----------------------------------------Change size---------------------------------------------------------

        void resize (size_type n, value_type val = value_type()) {
            (void) val; // for initial testing only
            if (n < _size) {
                node *currentNode = _tail->previous->previous, *toDelete = currentNode->next;
                for (; n != _size; --_size) {
                    destroyAndDeallocateNode(toDelete);
                    currentNode = currentNode->previous;
                    toDelete = currentNode->next;
                }
                currentNode->next->next = _tail;
                _tail->previous = currentNode->next;
            }
            else {
                for (size_type size = n - _size; size; --size) {
                    push_back(val);
                };
            }
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

        // -----------------------------------------OPERATIONS----------------------------------------------------------

        // -----------------------------------------Transfer elements from list to list---------------------------------

        void splice(iterator position, list& x) {
            if (x._size) {
                node *f = x._tail->next, *l = x._tail->previous;
                unlinkNodes(&f, &l);
                linkNodes(&position._node, &f, &l);
                _size += x._size;
                x._size = 0;
            }
        }

        void splice(iterator position, list& x, iterator i) {
            if (position._node != i._node && position._node != i._node->next) {

                unlinkNodes(&i._node, &i._node);
                --x._size;
                linkNodes(&position._node, &i._node, &i._node);
                ++_size;
            }
        }

        void splice(iterator position, list& x, iterator first, iterator last) {
            if (first != last) {
                if (this != &x) {
                    size_type countNode = ft::distance(first, last);
                    x._size -= countNode;
                    _size += countNode;
                }
                --last;
                unlinkNodes(&first._node, &last._node);
                linkNodes(&position._node, &first._node, &last._node);
            }
        }

        // -----------------------------------------Remove Elements With Specific Value---------------------------------

        void remove(const value_type& val) {
            for (node *start = _tail->next, *toDelete = nullptr; start != _tail; start = start->next) {
                if (start->value_type == val) {
                    toDelete = start;
                    destroyAndDeallocateNode(toDelete);
                    unlinkNode(&toDelete);
                    --_size;
                }
            }
        }

        // -----------------------------------------Remove Elements Fulfilling Condition--------------------------------

        template <class Predicate>
        void remove_if (Predicate pred) {
            for (node *start = _tail->next, *toDelete = nullptr; start != _tail; start = start->next) {
                if (pred(start->value_type)) {
                    toDelete = start;
                    destroyAndDeallocateNode(toDelete);
                    unlinkNode(&toDelete);
                    --_size;
                }
            }
        }

        // -----------------------------------------Remove duplicate values---------------------------------------------

        void unique() {
            unique(ft::equalTo<value_type>());
        }

        template <class BinaryPredicate>
        void unique (BinaryPredicate binary_pred) {
            node *second = _tail->next->next;

            while (second != _tail) {
                if (binary_pred(second->value_type, second->previous->value_type)) {
                    second = second->next;
                    unlinkNode(&second->previous);
                    destroyAndDeallocateNode(second->previous);
                    --_size;
                }
                else {
                    second = second->next;
                }
            }
        }

        // -----------------------------------------Merge Sorted Lists--------------------------------------------------

        void merge (list& x) {
            merge(x, ft::less<value_type>());
        }

        template <class Compare>
        void merge (list& x, Compare comp) {
            if (this != &x) {
                node *first1 = _tail->next, *first2 = x._tail->next;

                while(first1 != _tail && first2 != x._tail) {
                    if (comp(first2->value_type, first1->value_type)) {
                        size_type size = 1;
                        node *tmp = first2->next;
                        for(; tmp != x._tail && comp(tmp->value_type, first1->value_type); tmp = tmp->next, ++size)
                            ;
                        _size += size;
                        x._size -= size;
                        node *f = first2, *l = tmp->previous;
                        first2 = tmp;
                        unlinkNodes(&f, &l);
                        tmp = first1->next;
                        linkNodes(&first1, &f, &l);
                        first1 = tmp;
                    }
                    else {
                        first1 = first1->next;
                    }
                }
                splice(end(), x);
            }
        }

        // -----------------------------------------Sort Elements In Container------------------------------------------

        void sort() {
            sort(ft::less<value_type>());
        }

        template <class Compare>
        void sort (Compare comp) {
            if (_size) {
                node *head = _tail->next, *lastBeforeSorted = nullptr;

                unlinkNode(&_tail);
                head->previous->next = nullptr;
                mergeSort(&head, comp);
                head->previous = _tail;
                _tail->next = head;
                for (lastBeforeSorted = head; lastBeforeSorted->next; lastBeforeSorted = lastBeforeSorted->next);
                _tail->previous = lastBeforeSorted;
                lastBeforeSorted->next = _tail;
            }
        }

        // -----------------------------------------Reverse The Order Of Elements---------------------------------------

        void reverse() {
            if (_size > 1) {
                for (node *toSwap = _tail->next; toSwap != _tail;) {
                    ft::swap(toSwap->previous, toSwap->next);
                    toSwap = toSwap->previous;
                }
                ft::swap(_tail->previous, _tail->next);
            }
        }

        // -----------------------------------------OBSERVERS-----------------------------------------------------------

        allocator_type get_allocator() const {
            return _alloc;
        }

        /*
        ** -----------------------------------------AUXILIARY FUNCTIONS-------------------------------------------------
        */

        // -----------------------------------------Allocate Memory-----------------------------------------------------

    };

    /*
    ** -----------------------------------------NON-MEMBER FUNCTIONS------------------------------------------------
    */

    // -----------------------------------------Relational Operators------------------------------------------------


    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    // -----------------------------------------Swap----------------------------------------------------------------

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
        x.swap(y);
    }
}



#endif //FT_VECTOR_H
