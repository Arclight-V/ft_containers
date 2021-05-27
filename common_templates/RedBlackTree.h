//
// Created by Arclight Natashia on 5/7/22.
//

#include "NodeTraits.h"
#include "stdafx.h"

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

namespace ft {

    template<class T, class Compare, class Alloc>
    class RedBlackTree {

        typedef T value_type;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename ft::NodeTraits<value_type>::_tn_list_TS_Ptr nodePtr;

        nodePtr _root;
        nodePtr _end;
        allocator_type _alloc;
        std::allocator<typename ft::NodeTraits<value_type>::_tn_list_TS> _allocNode;
        value_compare _comp;
        size_type _size;

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

        // -----------------------------------------ALLOCATOR-----------------------------------------------------------

        allocator_type get_allocator() const {
            return _alloc;
        }
    };
}

#endif //REDBLACKTREE_H