//
// Created by Arclight Natashia on 5/26/21.
//

#ifndef MAPITERATOR_H
#define MAPITERATOR_H

#include "../common_templates/baseIterator.h"
#include "ft_map.h"
#include <map>

// BIDIRECTIONAL ITERATOR
namespace ft {

    template<class T> class MapIterator;
    template<class T, class PointerT> class MapConstIterator;

    template<class T>
    class MapIterator : public ft::baseIterator<std::bidirectional_iterator_tag, T > {
        typedef typename ft::NodeTraits<T>::_tn_list_TS                     node;
        node *_node;

        template<class, class> friend class MapConstIterator;
        template<class, class, class, class> friend class map;
    public:

        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        // default-constructor
        explicit MapIterator(Node *ptr = nullptr) : _node(ptr) {};

        // copy-constructor
        MapIterator(MapIterator<T> const &x) : _node(x._node) {};

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------

        virtual ~MapIterator() {};

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        MapIterator &operator=(MapIterator const &x) {
            if (this != &x) {
                _node = x._node;
            }
            return *this;
        }

        // Can be compared for equivalence using the equality/inequality operators
        // (meaningful when both iterator values iterate over the same underlying sequence)
        bool operator==(MapIterator const &x) {
            return _node == x._node;
        }

        bool operator!=(MapIterator const &x) {
            return _node != x._node;
        }

        // Can be dereferenced as an rvalue (if in a dereferenceable state)
        typename MapIterator::reference operator*() const {
            return _node->value_type;
        }

        typename MapIterator::pointer operator->() const {
            return &_node->value_type;
        }

        // Can be incremented (if in a dereferenceable state).
        // The result is either also dereferenceable or a past-the-end iterator.
        // Two iterators that compare equal, keep comparing equal after being both increased
//        MapIterator operator++() {
//            _node = _node->next;
//            return *this;
//        }
//
//        MapIterator operator++(int) {
//            MapIterator ret(*this);
//            _node = _node->next;
//            return ret;
//        }
//
//        // Can be decremented (if a dereferenceable iterator value precedes it).
//        MapIterator operator--() {
//            _node = _node->previous;
//            return *this;
//        }
//
//        MapIterator operator--(int) {
//            MapIterator ret(*this);
//            _node = _node->previous;
//            return ret;
//        }
    };

    template<class T, class PointerT>
    class MapConstIterator : public ft::baseIterator<std::bidirectional_iterator_tag, T, PointerT> {
        typedef typename ft::NodeTraits<T>::_dl_list_TS                     Node;
        Node *_node;

        template<class, class, class, class> friend class map;

    public:

        explicit MapConstIterator(Node *ptr = nullptr) : _node(ptr) {};

        MapConstIterator(MapIterator<T> const &x) : _node(x._node) {};

        virtual ~MapConstIterator() {};

        MapConstIterator &operator=(MapConstIterator const &x) {
            if (this != &x) {
                _node = x._node;
            }
            return *this;
        }

        bool operator==(MapConstIterator const &x) {
            return _node == x._node;
        }

        bool operator!=(MapConstIterator const &x) {
            return _node != x._node;
        }

        typename MapConstIterator::reference operator*() const {
            return _node->value_type;
        }

        typename MapConstIterator::pointer operator->() const {
            return &_node->value_type;
        }

//        MapConstIterator operator++() {
//            _node = _node->next;
//            return *this;
//        }
//
//        MapConstIterator operator++(int) {
//            MapConstIterator ret(*this);
//            _node = _node->next;
//            return ret;
//        }
//
//        MapConstIterator operator--() {
//            _node = _node->previous;
//            return *this;
//        }
//
//        MapConstIterator operator--(int) {
//            MapConstIterator ret(*this);
//            _node = _node->previous;
//            return ret;
//        }
    };
}

#endif //MAPITERATOR_H
