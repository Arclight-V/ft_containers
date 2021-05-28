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
            _end->color = NONE;
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

    private:
        void findMinimumInTree() {
            nodePtr tmp = _root;

            while (tmp->left) {
                tmp = tmp->left;
            }
            _end->left = tmp;
        }

        void findMaximumInTree() {
            nodePtr  tmp = _root;

            while (tmp->right) {
                tmp = tmp->right;
            }
            _end->right = tmp;
        }

        void rotateRight(nodePtr x) {
            // rotate node x to right
            nodePtr y = x->left;

            // establish x->left link
            x->left = y->right;
            if (y->right) {
                y->right->parent = x;
            }
            // establish y->parent link
            y->parent = x->parent;
            if (!x->parent) {
                _root = y;
            }
            else if (x = x->parent->right) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            // link x and y
            y->right = x;
            x->parent = y;
        }

        void rotateLeft(nodePtr x) {
            // rotate node x to left
            nodePtr y = x->right;

            // establish x->right link
            x->right = y->left;
            if (y->left) {
                y->left->parent = x;
            }
            // establish y->parent link
            if (!x->parent) {
                _root = y;
            }
            else if (x == x->parent->left) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            // link x and y
            x->left = x;
            x->parent = y;
        }

        insertFixup(nodePtr x) {
            // maintain red-black property after insertion
            nodePtr child;

            while (x->parent->color == RED) {
                // we have a violation
                if (x->parent == x->parent->parent->left) {
                    child = x->parent->parent->right;
                    if (child->color == RED ) {
                        // uncle is RED
                        child->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    }
                    else {
                        // uncle is BLACK
                        if ( x == x->parent->right) {
                            // make x a left child
                            x = x->parent;
                            rotateLeft(x);
                        }
                        // recolor and rotate
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotateRight(x->parent->parent);
                    }
                }
                else {
                    // mirror image of above code
                    child = x->parent->parent->left;
                    if (child->color == RED) {
                        // uncle is RED
                        child->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x->parent->parent;
                    }
                    else {
                        // uncle is BLACK
                        if (x == x->parent->left) {
                            x = x->parent;
                            roetateRight(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotateLeft(x->parent->parent)
                    }
                }
                if (x == _root) {
                    break;
                }
            }
            _root->color = BLACK;
        }

    public:
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
            findMinimumInTree();
            findMaximumInTree();
            return std::pair<iterator(x), true>;
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
            newNode->color = RED;
            return  newNode;
        }
    };
}

#include "../ft_map/mapIterator.h"

#endif //REDBLACKTREE_H
