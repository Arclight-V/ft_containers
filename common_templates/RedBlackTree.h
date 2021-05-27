//
// Created by Arclight Natashia on 5/7/22.
//

#include "stdafx.h"
#include "NodeTraits.h"
#include "Algorithm.h"

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

namespace ft {
    template<class T, class Compare, class Alloc>
        class RedBlackTree {

        typedef T                                                               value_type;
        typedef Compare                                                         value_compare;
        typedef Alloc                                                           allocator_type;
        typedef typename allocator_type::size_type                              size_type;
        typedef typename ft::NodeTraits<value_type>::_tn_list_TS_Ptr            nodePtr;
        typedef typename ft::MapIterator<value_type>                            iterator;
        typedef typename ft::MapConstIterator<value_type, value_type const *>   const_iterator;
        typedef typename ft::ReverseIterator<iterator>                          reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator>                    const_reverse_iterator;

        nodePtr                                                                 _root;
        nodePtr                                                                 _end;
        allocator_type                                                          _alloc;
        std::allocator<typename ft::NodeTraits<value_type>::_tn_list_TS>        _allocNode;
        value_compare                                                           _comp;
        size_type                                                               _size;

    public:

        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        explicit RedBlackTree(const value_compare &compare) : _root(nullptr),
                                                              _alloc(allocator_type()), _comp(compare), _size(0) {
            _end = _allocNode.allocate(1);
            std::memset(&_end->value_type, 0, sizeof(value_type));
            _end->parent = _end;
            _end->left = _end;
            _end->right = _end;
            _end->color = ft::NodeTraits<value_type>::NONE;
        }

        // -----------------------------------------CAPACITY------------------------------------------------------------

        bool empty() const {
            return _size == 0;
        }

        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        // -----------------------------------------MODIFIERS-----------------------------------------------------------

        // -----------------------------------------Insert elements-----------------------------------------------------
        std::pair<iterator, bool> insertUnique(const value_type& val) {
            nodePtr current, parent, x;

            current = _root;
            parent = nullptr;

            // find where node
            while (current) {
                if (val == current->value_type) {
                    return std::pair<iterator(current), false>;
                }
                parent = current;
                current = _comp(val, current->value_type) ? current->left : current->right;
            }
            x = allocateNewNode(val, parent);

            // insert node in tree

            if (parent) {
                if (_comp(val, parent->value_type)) {
                    parent->left = x;
                }
                else {
                    parent->right = x;
                }
            }
            else {
                root = x;
            }
            isertFixup(x);
            return std::pair<iterator(current), true>;
        }

        // -----------------------------------------ALLOCATOR-----------------------------------------------------------

        allocator_type get_allocator() const {
            return _alloc;
        }

        private:

        /*
        ** -----------------------------------------AUXILIARY FUNCTIONS-------------------------------------------------
        */
        // -----------------------------------------Allocate Memory-----------------------------------------------------

        nodePtr allocateNewNode(const value_type& val, nodePtr parent) {
            nodePtr newNode = _allocNode.allocate(1);

            _alloc.construct(&newNode->value_type, val);
            newNode->parent = parent;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->color = ft::NodeTraits<value_type>::RED;
            return  newNode;
        }
    };
}

#include "../ft_map/mapIterator.h"

#endif //REDBLACKTREE_H
