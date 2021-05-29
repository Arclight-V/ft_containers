//
// Created by Arclight Natashia on 5/7/22.
//

#include "stdafx.h"
#include "NodeTraits.h"
#include "../ft_map/mapIterator.h"

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
        nodePtr                                                                 _TNULL;
        allocator_type                                                          _alloc;
        std::allocator<typename ft::NodeTraits<value_type>::_tn_list_TS>        _allocNode;
        value_compare                                                           _comp;
        size_type                                                               _size;

    public:

        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        explicit RedBlackTree(const value_compare &compare, const allocator_type& alloc = allocator_type()) : _root(nullptr), _alloc(alloc), _comp(compare), _size(0) {
            _end = _allocNode.allocate(1);
            std::memset(&_end->value_type, 0, sizeof(value_type));
            _end->parent = _end;
            _end->left = _end;
            _end->right = _end;
            _end->color = NONE;

            _TNULL = _allocNode.allocate(1);
            std::memset(&_TNULL->value_type, 0, sizeof(value_type));
            _TNULL->left = nullptr;
            _TNULL->right = nullptr;
            _TNULL->color = BLACK;

            _root = _TNULL;

        }

        // -----------------------------------------ITERATORS-----------------------------------------------------------

        iterator begin() {
            return iterator(_end->left);
        }

        iterator end() {
            return iterator(_end);
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

        void configureEndNode() {
            findMinimumInTree();
            findMaximumInTree();
            linkEndFromTree();
        }
        void unlinkEndFromTree() {
            if (_end->right) {
                _end->right->right = _TNULL;
            }
        }

        void linkEndFromTree() {
            _end->right->right = _end;
        }

        void findMinimumInTree() {
            nodePtr tmp = _root;

            while (tmp->left != _TNULL) {
                tmp = tmp->left;
            }
            _end->left = tmp;
        }

        void findMaximumInTree() {
            nodePtr  tmp = _root;

            while (tmp->right != _TNULL) {
                tmp = tmp->right;
            }
            _end->right = tmp;
        }

        void rotateRight(nodePtr x) {
            // rotate node x to right
            nodePtr y = x->left;

            // establish x->left link
            x->left = y->right;
            if (y->right != _TNULL) {
                y->right->parent = x;
            }
            // establish y->parent link
            y->parent = x->parent;
            if (!x->parent) {
                _root = y;
            }
            else if (x == x->parent->right) {
                x->parent->right = y;
            }
            else {
                x->parent->left = y;
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
            if (y->left != _TNULL) {
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

        void insertFixup(nodePtr x) {
            // maintain red-black property after insertion
            nodePtr child;

            while (x->parent->color == RED) {
                // we have a violation
                if (x->parent == x->parent->parent->right) {
                    child = x->parent->parent->left;
                    if (child->color == RED ) {
                        // uncle is RED
                        child->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    }
                    else {
                        // uncle is BLACK
                        if ( x == x->parent->left) {
                            // make x a right child
                            x = x->parent;
                            rotateRight(x);
                        }
                        // recolor and rotate
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotateLeft(x->parent->parent);
                    }
                }
                else {
                    // mirror image of above code
                    child = x->parent->parent->right;
                    if (child->color == RED) {
                        // uncle is RED
                        child->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    }
                    else {
                        // uncle is BLACK
                        if (x == x->parent->right) {
                            x = x->parent;
                            // make x a left child
                            rotateLeft(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotateRight(x->parent->parent);
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
            unlinkEndFromTree();

            nodePtr y = nullptr, x = _root, newNode;

            while (x != _TNULL) {
                y = x;
                if (val.first == x->value_type.first) {
                    configureEndNode();
                    return std::make_pair(iterator(x), false);
                }
                x = _comp(val.first, x->value_type.first) ? x->left : x->right;
            }

            newNode = allocateNewNode(val, y);

            if (y == nullptr) {
                _root = newNode;
            }
            else if (_comp(newNode->value_type.first, y->value_type.first)) {
                y->left = newNode;
            }
            else {
                y->right = newNode;
            }

            if (!newNode->parent) {
                newNode->color = BLACK;
                configureEndNode();
                return std::make_pair(iterator(newNode), true);
            }

            if (!newNode->parent->parent) {
                configureEndNode();
                return std::make_pair(iterator(newNode), true);
            }

            insertFixup(newNode);
            configureEndNode();
            return std::make_pair(iterator(newNode), true);
        }


        // -----------------------------------------ALLOCATOR-----------------------------------------------------------

        allocator_type get_allocator() const {
            return _alloc;
        }

        void printTree() {
            unlinkEndFromTree();
            if (_root) {
                printHelper(_root, "", true);
            }
            linkEndFromTree();
        }




        private:
            void printHelper(nodePtr root, std::string indent, bool last) {
                if (root != _TNULL) {
                    std::cout << indent;
                    if (last) {
                        std::cout << "R----";
                        indent += "   ";
                    } else {
                        std::cout << "L----";
                        indent += "|  ";
                    }

                    std::string sColor = root->color == RED ? "RED" : "BLACK";
                    std::cout << root->value_type.first << "(" << sColor << ")" << std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
            }

        /*
        ** -----------------------------------------AUXILIARY FUNCTIONS-------------------------------------------------
        */
        // -----------------------------------------Allocate Memory-----------------------------------------------------

        nodePtr allocateNewNode(const value_type& val, nodePtr parent) {
            nodePtr newNode = _allocNode.allocate(1);

            _alloc.construct(&newNode->value_type, val);
            newNode->parent = parent;
            newNode->left = _TNULL;
            newNode->right = _TNULL;
            newNode->color = RED;
            return  newNode;
        }
    };
}

#endif //REDBLACKTREE_H
