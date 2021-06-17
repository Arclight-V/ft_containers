//
// Created by Arclight Natashia on 5/26/21.
//

#ifndef MAPITERATOR_H
#define MAPITERATOR_H

#include "../common_templates/baseIterator.h"
#include "../common_templates/NodeTraits.h"
#include "../common_templates/Algorithm.h"

#include <map>

// BIDIRECTIONAL ITERATOR
namespace ft {
    template<class T, class Compare> class MapIterator;
    template<class T, class PointerT, class Compare> class MapConstIterator;

    template<class T, class Compare>
    class MapIterator : public ft::baseIterator<std::bidirectional_iterator_tag, T > {
        typedef typename ft::NodeTraits<T>::_tn_list_TS_Ptr                     nodePtr;
        typedef Compare                                                         key_compare;

        nodePtr                                                                 _node;
        key_compare                                                             _comp;

        template<class, class, class> friend class MapConstIterator;
        template<class, class, class, class> friend class map;
        template<class, class, class, class> friend class RedBlackTree;

    public:

        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        // default-constructor
        explicit MapIterator(nodePtr ptr = nullptr) : _node(ptr) {};

        // copy-constructor
        MapIterator(MapIterator const &x) : _node(x._node) {};

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
        MapIterator operator++() {
                nodePtr tmp = _node;

                if (_node->right->right)
                {
                    tmp = _node->right;
                    while (tmp->left && tmp->left->left && tmp->left != _node)
                        tmp = tmp->left;
                }
                else if (_node->parent)
                {
                    tmp = _node->parent;
                    while (tmp->parent && _comp(tmp->value_type.first, _node->value_type.first))
                    {
                        tmp = tmp->parent;
                    }
                }
                _node = tmp;
                return (*this);
        }

        MapIterator operator++(int) {
            MapIterator ret(*this);
            operator++();
            return ret;
        }

        // Can be decremented (if a dereferenceable iterator value precedes it).
        MapIterator operator--() {
            nodePtr tmp = _node;

            if (_node->left->left)
            {
                tmp = _node->left;
                while (tmp->right && tmp->right->right && tmp->right != _node)
                    tmp = tmp->right;
            }
            else if (_node->parent)
            {
                tmp = _node->parent;
                while (tmp->parent && _comp(_node->value_type.first, tmp->value_type.first))
                {
                    tmp = tmp->parent;
                }
            }
            _node = tmp;
            return (*this);

        }

        MapIterator operator--(int) {
            MapIterator ret(*this);
            _node = _node->previous;
            return ret;
        }
    };

    template<class T, class PointerT, class Compare>
    class MapConstIterator : public ft::baseIterator<std::bidirectional_iterator_tag, T, PointerT> {
        typedef typename ft::NodeTraits<T>::_tn_list_TS_Ptr                     nodePtr;
        typedef Compare                                                         key_compare;

        nodePtr                                                                 _node;
        key_compare                                                             _comp;

        template<class, class, class, class> friend class map;

    public:

        explicit MapConstIterator(nodePtr ptr = nullptr) : _node(ptr) {};

        MapConstIterator(MapIterator<T, Compare> const &x) : _node(x._node) {};

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

// Can be incremented (if in a dereferenceable state).
        // The result is either also dereferenceable or a past-the-end iterator.
        // Two iterators that compare equal, keep comparing equal after being both increased
        MapConstIterator operator++() {
            nodePtr tmp = _node;

            if (_node->right->right)
            {
                tmp = _node->right;
                while (tmp->left->left && tmp->left != _node)
                    tmp = tmp->left;
            }
            else if (_node->parent)
            {
                tmp = _node->parent;
                while (tmp->parent && _comp(tmp->value_type.first, _node->value_type.first))
                {
                    tmp = tmp->parent;
                }
            }
            _node = tmp;
            return (*this);
        }

        MapConstIterator operator++(int) {
            MapConstIterator ret(*this);
            operator++();
            return ret;
        }

        // Can be decremented (if a dereferenceable iterator value precedes it).
        MapConstIterator operator--() {
            nodePtr tmp = _node;

            if (_node->left->left)
            {
                tmp = _node->left;
                while (tmp->right->right && tmp->right != _node)
                    tmp = tmp->right;
            }
            else if (_node->parent)
            {
                tmp = _node->parent;
                while (tmp->parent && _comp(_node->value_type.first, tmp->value_type.first))
                {
                    tmp = tmp->parent;
                }
            }
            _node = tmp;
            return (*this);
        }

        MapConstIterator operator--(int) {
            MapConstIterator ret(*this);
            _node = _node->previous;
            return ret;
        }
    };
}
#include "../ft_map/ft_map.h"
#endif //MAPITERATOR_H
