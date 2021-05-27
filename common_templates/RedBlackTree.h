//
// Created by Arclight Natashia on 5/7/22.
//

#include "NodeTraits.h"
#include "stdafx.h"

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

namespace ft {

    template < class T, class Compare , class Alloc >
    class RedBlackTree {

        public:
            typedef T                                       value_type;
            typedef Compare                                 value_compare;
            typedef Alloc                                   allocator_type;
        
        private:
            typedef typename ft::NodeTraits::_tn_list_TS_Ptr    nodePtr;
            nodePtr                                             _root;
            nodePtr                                             _end;
            allocator_type                                      _alloc;
            std::allocator<ft::NodeTraits::_tn_list_TS>         _allocNode;
            value_compare                                       _comp ;
            

        public:

            RedBlackTree() : _root(nullptr), _end(_allocNode.allocate(1)), _alloc(allocator_type()) {
                _end = _allocNode.allocate(1);
                std::memset(&_end->value_type, 0, sizeof(value_type));
                _end->parent = _end;
                _end->left = _end;
                _end->right = _end;
                _node->color = NodeTraits<int>::nodeColor::NONE;
            }
    }; 
};

#endif //REDBLACKTREE_H