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

#define MUlTIPLIER_CAPACITY 2
#define DIVISOR_CAPACITY    0.5
//#define START_CAPACITY      100



namespace ft {
    template < class T, class Alloc = std::allocator<T> >
    class vector {

    public:
        typedef T                                                                   value_type;
        typedef Alloc                                                               allocator_type;
        typedef typename allocator_type::reference                                  reference;
        typedef typename allocator_type::const_reference                            const_reference;
        typedef typename allocator_type::pointer                                    pointer;
        typedef typename allocator_type::const_pointer                              const_pointer;

        typedef typename ft::VectorIterator<value_type, value_type *>               iterator;
        typedef typename ft::VectorIterator<value_type, value_type const *>         const_iterator;
        typedef typename ft::ReverseIterator<iterator>                              reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator>                        const_reverse_iterator;
        typedef typename ft::VectorIterator<value_type, value_type *>::difference_type            difference_type;
        typedef size_t                                                              size_type;

    private:
        allocator_type                                                              _alloc;
        size_type                                                                   _size;
        size_type                                                                   _capacity;
        pointer                                                                     _begin;
        pointer                                                                     _end;

    public:
        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        // Empty container constructor (default constructor)
        // Constructs an empty container, with no elements.

        explicit vector (const allocator_type& alloc = allocator_type()) :  _alloc(alloc),
                                                                            _size(0),
                                                                            _capacity(0),
                                                                            _begin(nullptr),
                                                                            _end(nullptr) {}

        //  Fill constructor
        //  Constructs a container with n elements. Each element is a copy of val.

        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(_size) {
            _begin = _alloc.allocate(_capacity + 1);
            size_type i = 0;
            pointer tmp = _begin;

            while (i < n) {
                _alloc.construct(tmp, val);
                ++i;
                ++tmp;
            }
            _end = tmp;
        }

        // Range constructor
        // Constructs a container with as many elements as the range [first,last), with each element constructed from
        // its corresponding element in that range, in the same order.

        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) :
                _alloc(alloc), _size(last._ptr - first._ptr), _capacity(_size) {
            (void)isIter;
            pointer firstPtr = first._ptr, lastPtr = last._ptr, tmp = _begin;
            _begin = _alloc.allocate(_capacity + 1);

            for (; firstPtr != lastPtr; ++firstPtr, ++tmp) {
                _alloc.construct(tmp, firstPtr);
            }
            _end = tmp;
        }

        //  Copy constructor
        //  Constructs a container with a copy of each of the elements in x, in the same order.

        vector (const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity) {
            _begin = _alloc.allocate(_capacity + 1);
            size_type i = 0;

            for (; i < x._size; ++i) {
                _alloc.construct(_begin + i, x[i]);
            }
            _end = _begin + i;
        }

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------

        virtual ~vector() {
            clear();
            deallocateMemory();
            _begin = nullptr;
            _end = nullptr;
            _capacity = 0;
        }

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        vector &operator=(const vector& x) {
            if (this != &x) {
                clear();
                _alloc = x._alloc;
                _size = x._size;
                _capacity = x._capacity;
                _begin = _alloc.allocate(_capacity + 1);
                size_type i = 0;
                for (; i < x._size; ++i) {
                    _alloc.construct(_begin + i, x[i]);
                }
                _end = _begin + i;
            }
            return *this;
        }

        // -----------------------------------------ITERATORS-----------------------------------------------------------

        iterator begin() {
            return iterator(_begin);
        };

        const_iterator begin() const {
            return const_iterator(_begin);
        };

        iterator end() {
            return iterator(_end);
        }

        const_iterator end() const {
            return const_iterator(_end);
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
        }

//        void resize(size_type n, value_type val = value_type()) {
////            if (n < _size) {
////                --_size;
////                for (; n != _size; --_size) {
////                    _alloc.destroy(_begin + _size);
////                }
////                _alloc.destroy(_begin + _size);
////                if ((_capacity / _size) >= 2) {
////                    size_type newCapacity = _capacity - _capacity / 4;
////                    pointer tmp = _begin + newCapacity;
////                    _alloc.deallocate(tmp, _capacity - newCapacity + 1);
////                }
////                _end = _begin + _size + 1;
////            }
////            else if (n > _size && n < _capacity) {
////                pointer tmp += _size;
////                for (; _size < n; ++_size) {
////                    _alloc.construct(_tmp, val);
////                }
////                _end = _begin + _size + 1;
////            }
////            else {
////                clear();
////
////            }
//        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        size_type capacity() const {
            return _capacity;
        }

        // -----------------------------------------Request a change in capacity----------------------------------------
        void reserve(size_type n) {
            if (n > _capacity) {

            }
        }


        // -----------------------------------------ELEMENT ACCESS------------------------------------------------------

        reference operator[] (size_type n) {
            return _begin[n];
        }

        const_reference operator[] (size_type n) const {
            return _begin[n];
        }

        reference at(size_type n) {
            return _begin[n];
        }

        const_reference at(size_type n) const {
            return _begin[n];
        }

/*
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
*/
        void push_back(value_type const &val) {
            if (_size + 1 > _capacity) {
                augmenterСapacity((_capacity = _capacity ? _capacity : 1) * MUlTIPLIER_CAPACITY);
                _alloc.construct(_end, val);
                ++_end;
            }
            else {
                _alloc.construct(_end, val);
                ++_end;
            }
            ++_size;
        }

        // -----------------------------------------Delete last element-------------------------------------------------


        void pop_back() {
            _alloc.destroy(--_end);
            --_size;
        }

        // -----------------------------------------Insert Elements-----------------------------------------------------

//        iterator insert (iterator position, const value_type& val) {
//
//            if ((_size + 1) >= _capacity) {
//                size_type newCapacity = _capacity * MUlTIPLIER_CAPACITY;
//                pointer newArray = _alloc.allocate(newCapacity + 1);
//                pointer tmpNewArray = newArray, tmpBegin = _begin, positionPtr = position._ptr;
//
//                for (; tmpBegin != positionPtr; ++tmpNewArray, ++tmpBegin) {
//                    _alloc.construct(tmpNewArray, tmpBegin);
//                }
//                _alloc.construct(tmpNewArray++, &val);
//                for (; tmpBegin != _end; ++tmpNewArray, ++tmpBegin) {
//                    _alloc.construct(tmpNewArray, tmpBegin);
//                }
//                destroyAllElements();
//                deallocateMemory();
//                ++_size;
//                _begin = newArray;
//                _end = tmpNewArray;
//                _capacity = newCapacity;
//            }
//            std::move(position._ptr + 1, _end, position._ptr);
//            _alloc.construct(position._ptr, &val);
//        }

//        void insert (iterator position, size_type n, const value_type& val) {
//
//        }
//
//        template <class InputIterator>
//        void insert (iterator position,
//                     InputIterator first,
//                     InputIterator last,
//                     typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) {
//            (void)isIter;
//
//        }



        // -----------------------------------------Erase Elements------------------------------------------------------

        iterator erase(iterator position) {
            pointer ptr = position._ptr;
            _alloc.destroy(ptr);
            std::move(ptr + 1, _end, ptr);
            --_size;
            --_end;
            return iterator(ptr);
        }

        iterator erase(iterator first, iterator last) {
            difference_type indexFirst = first._ptr - _begin, indexLast = last._ptr - _begin;
            pointer ptr = _begin + (first._ptr - _begin);
            if (first != last) {
                for (pointer tmp = first._ptr; tmp != first._ptr; ++last._ptr) {
                    _alloc.destroy(tmp);
                }
                std::move(ptr + (indexLast - indexFirst), _end, ptr);
            }
            _size -= indexLast - indexFirst;
            _end = _begin + _size;
            return iterator(ptr);
        }

        /*
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

 */
        void clear() {
            if (!_begin) {
                return;
            }
            destroyAllElements();
            _size = 0;
        }
/*
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

 */

        /*
        ** -----------------------------------------AUXILIARY FUNCTIONS-------------------------------------------------
        */

        // -----------------------------------------Allocate Memory-----------------------------------------------------
        void augmenterСapacity(size_type newCapacity) {
            pointer newArray = _alloc.allocate(newCapacity + 1);
            pointer tmp = newArray, begin = _begin;
            for (;begin != _end; ++begin, ++tmp) {
                _alloc.construct(tmp, *begin);
            }
            destroyAllElements();
            deallocateMemory();
            _begin = newArray;
            _end = tmp;
            _capacity = newCapacity;
        }

        // -----------------------------------------Deallocate Memory---------------------------------------------------

        void destroyAllElements() {
            for(pointer tmp = _begin; tmp != _end; ++tmp) {
                _alloc.destroy(tmp);
            }
        }

        void deallocateMemory() {
            _alloc.deallocate(_begin, _capacity);
        }



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
