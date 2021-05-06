//
// Created by Arclight Natashia on 5/4/21.
//

#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "baseIterator.h"

//#include "stdafx.h"

// BIDIRECTIONAL ITERATOR

namespace ft {

    template<class Node>
class ListIterator : public ft::baseIterator<std::bidirectional_iterator_tag, Node> {
    private:
        Node *_node;
    public:
        /*
        // defining iterator types
        typedef Node                                        value_type;
        typedef typename std::ptrdiff_t                     difference_type;
        typedef Node*                                       pointer;
        typedef Node&                                       reference;
        typedef typename std::bidirectional_iterator_tag    iterator_category;
        */
        /*
         * Requirements for a bidirectional iterator
         */
        // default-constructor
        ListIterator() : _node(nullptr) {};

        // copy-constructor
        ListIterator(Node const &x) : _node(x._node) {};

        // destructor
        virtual ~ListIterator() {};

        // copy-assignable
        ListIterator &operator=(ListIterator const &x) {
            if (this != x) {
                _node = x._node;
            }
            return *this;
        }

        // Can be compared for equivalence using the equality/inequality operators
        // (meaningful when both iterator values iterate over the same underlying sequence)
        bool operator==(ListIterator const &x) {
            return _node == x._node;
        }

        bool operator!=(ListIterator const &x) {
            return _node != x._node;
        }

        // Can be dereferenced as an rvalue (if in a dereferenceable state)
        typename ft::baseIterator<std::bidirectional_iterator_tag, Node>::reference operator*(){
            return _node->value;
        }

        typename ft::baseIterator<std::bidirectional_iterator_tag, Node>::pointer operator->(){
            return &_node->value;
        }

        // Can be incremented (if in a dereferenceable state).
        // The result is either also dereferenceable or a past-the-end iterator.
        // Two iterators that compare equal, keep comparing equal after being both increased
        ListIterator operator++() {
            _node = _node->next;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator ret(*this);
            _node = _node->next;
            return ret;
        }

        // Can be decremented (if a dereferenceable iterator value precedes it).
        ListIterator operator--() {
            _node = _node->previous;
            return *this;
        }

        ListIterator operator--(int) {
            ListIterator ret(*this);
            _node = _node->previous;
            return ret;
        }
    };
}

#endif //LISTITERATOR_H
