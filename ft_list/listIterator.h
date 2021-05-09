//
// Created by Arclight Natashia on 5/4/21.
//

#ifndef LISTITERATOR_H
#define LISTITERATOR_H

//#include "baseIterator.h"
//#include "stdafx.h"

#include "NodeTraits.h"
#include "ft_list.h"
#include <list>

// BIDIRECTIONAL ITERATOR
namespace ft {

    template<class T> class ListIterator;
    template<class T, class PointerT> class ListConstIterator;

    template<class T>
    class ListIterator : public ft::baseIterator<std::bidirectional_iterator_tag, T > {
        typedef typename ft::NodeTraits<T>::_dl_list_TS                     Node;
        Node *_node;

        template<class, class> friend class ListConstIterator;
        template<typename, typename> friend class list;

    public:

        /*
         * Requirements for a bidirectional iterator
         */
        // default-constructor
        explicit ListIterator(Node *ptr = nullptr) : _node(ptr) {};

        // copy-constructor
        ListIterator(ListIterator<T> const &x) : _node(x._node) {};

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
        typename ListIterator::reference operator*() const {
            return _node->value_type;
        }

        typename ListIterator::pointer operator->() const {
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

    template<class T, class PointerT>
    class ListConstIterator : public ft::baseIterator<std::bidirectional_iterator_tag, T, PointerT> {
        typedef typename ft::NodeTraits<T>::_dl_list_TS                     Node;
        Node *_node;
    public:
        /*
         * Requirements for a bidirectional iterator
         */
        // default-constructor
        explicit ListConstIterator(Node *ptr = nullptr) : _node(ptr) {};

        // copy-constructor
        ListConstIterator(ListIterator<T> const &x) : _node(x._node) {};

        // destructor
        virtual ~ListConstIterator() {};

        // copy-assignable
        ListConstIterator &operator=(ListConstIterator const &x) {
            if (this != x) {
                _node = x._node;
            }
            return *this;
        }

        // Can be compared for equivalence using the equality/inequality operators
        // (meaningful when both iterator values iterate over the same underlying sequence)
        bool operator==(ListConstIterator const &x) {
            return _node == x._node;
        }

        bool operator!=(ListConstIterator const &x) {
            return _node != x._node;
        }

        // Can be dereferenced as an rvalue (if in a dereferenceable state)
        typename ListConstIterator::reference operator*() const {
            return _node->value;
        }

        typename ListConstIterator::pointer operator->() const {
            return &_node->value;
        }


        // Can be incremented (if in a dereferenceable state).
        // The result is either also dereferenceable or a past-the-end iterator.
        // Two iterators that compare equal, keep comparing equal after being both increased
        ListConstIterator operator++() {
            _node = _node->next;
            return *this;
        }

        ListConstIterator operator++(int) {
            ListConstIterator ret(*this);
            _node = _node->next;
            return ret;
        }

        // Can be decremented (if a dereferenceable iterator value precedes it).
        ListConstIterator operator--() {
            _node = _node->previous;
            return *this;
        }

        ListConstIterator operator--(int) {
            ListConstIterator ret(*this);
            _node = _node->previous;
            return ret;
        }
    };
}

#endif //LISTITERATOR_H
