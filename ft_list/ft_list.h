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
             insertingNodeBefore(&_tail->previous, &_tail->next);
             destroyAndDeallocateNode(_tail->next);
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
                node *BeginX = x._tail->next, *prevEndX = x._tail->previous;
                prevEndX->next->next = prevEndX->next;
                prevEndX->next->previous = prevEndX->next;
                position._node->previous->next = BeginX;
                BeginX->previous = position._node->previous;
                position._node->previous = prevEndX;
                prevEndX->next = position._node;
                _size += x._size;
                x._size = 0;
            }
        }

        void splice(iterator position, list& x, iterator i) {
            if (position._node != i._node && position._node != i._node->next) {

                i._node->next->previous = i._node->previous;
                i._node->previous->next = i._node->next;
                --x._size;

                insertingNodeBefore(&i._node, &position._node);
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
                last._node->previous->next = position._node;
                first._node->previous->next = last._node;
                position._node->previous->next = first._node;

                node *tmp = first._node->previous;
                first._node->previous = position._node->previous;
                position._node->previous = last._node->previous;
                last._node->previous = tmp;
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
            unique(ft::equalTo());
        }

        template <class BinaryPredicate>
        void unique (BinaryPredicate binary_pred) {
            node *second = _tail->next->next;

            while (second != _tail) {
                if (binary_pred(second->value_type, second->previous->value_type)) {
                    second = second->next;
                    destroyAndDeallocateNode(second->previous);
                    unlinkNode(&second->previous);
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

        /*
        template <class Compare>
        void merge (list& x, Compare comp) {
            if (this != &x) {
                node *first1 = _tail->next, *end1 = _tail, *first2 = x._tail->next, *end2 = x._tail;

                while(first1 != end1 && first2 != end2) {
                    if (comp(first1->value_type, first2->value_type)) {
                        size_type size = 1;
                        node *tmp = first2->next;
                        for(; tmp !=end2 && comp(tmp->value_type, first1->value_type); tmp = tmp->next, ++size)
                            ;
                        _size += size;
                        x._size -= size;
                        node *f = first2, *l = tmp->previous;
                        first2 = tmp;

                    }
                }
            }
        }


        */

        // -----------------------------------------Sort Elements In Container------------------------------------------


        void sort() {
            sort(ft::less<value_type>());
        }

        template <class Compare>
        void sort (Compare comp) {
            node *head = _tail->next, *lastBeforeSorted = nullptr;

            unlinkNode(&_tail);
            head->previous->next = nullptr;
            mergeSort(&head, &lastBeforeSorted, comp);
            head->previous = _tail;
            _tail->next = head;
            _tail->previous = lastBeforeSorted;
            lastBeforeSorted->next = _tail;
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

        // -----------------------------------------Inserting Node Before-----------------------------------------------

        void insertingNodeBefore(node **node1, node **node2) {
            (*node1)->next = *node2;
            (*node1)->previous = (*node2)->previous;
            (*node2)->previous->next = *node1;
            (*node2)->previous = *node1;
        }

        // -----------------------------------------Inserting Node After------------------------------------------------
        void insertingNodeAfter(node **t, node **x) {
            (*t)->next = (*x)->next;
            (*x)->next->previous = *t;

            (*x)->next = *t;
            (*t)->previous = *x;
        }

        // -----------------------------------------Unlink Nodes--------------------------------------------------------

        void unlinkNode(node **toDelete) {
            (*toDelete)->next->previous =(*toDelete)->previous;
            (*toDelete)->previous->next = (*toDelete)->next;
        }

        void unlinkNodes(node **first, node **last) {
            (*first)->previous->next = (*last)->next;
            (*last)->previous = (*first)->previous;
        }

        // -----------------------------------------Insert Element------------------------------------------------------

        void executeInsert(node **newNode, node **positionNode, value_type const &val) {
            allocateMemoryForNodeAndConstruct(val, newNode);
            insertingNodeBefore(newNode, positionNode);
            ++_size;
        }

        // -----------------------------------------Merge Sort----------------------------------------------------------
        template <class Compare>
        node *mergeSortedLists(node *head1, node *head2, node **last, Compare comp){
            if (!head1) {
                return head2;
            }
            if (!head2) {
                return head1;
            }
            if (comp(head1->value_type, head2->value_type)) {
                *last = head2;
                head1->next = mergeSortedLists(head1->next, head2, last, comp);
                head1->next->previous = head1;
                head1->previous = nullptr;
                return head1;
            }
            head2->next = mergeSortedLists(head1, head2->next, last, comp);
            head2->next->previous = head2;
            head2->previous = nullptr;
            return head2;
        }

        void splitList(node *src, node **fRef, node **bRef) {
            node *fast = src->next, *slow = src;
            while (fast) {
                fast = fast->next;
                if (fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            *fRef = src;
            *bRef = slow->next;
            slow->next = nullptr;
        }
        template <class Compare>
        void mergeSort(node **head, node **last, Compare comp) {
            node *p = *head, *a = nullptr, *b = nullptr;
            if (p->next) {
                splitList(p, &a, &b);
                mergeSort(&a, last, comp);
                mergeSort(&b, last, comp);
                *head = mergeSortedLists(a, b, last, comp);
            }
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
