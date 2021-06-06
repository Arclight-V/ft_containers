//
// Created by Arclight Natashia on 5/7/22.
//

#include "stdafx.h"
#include "NodeTraits.h"
#include "../ft_map/mapIterator.h"

#include <iomanip>

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

namespace ft {
    template<class Key, class T, class Compare, class Alloc>
    class RedBlackTree {

        typedef Key key_type;
        typedef T value_type;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename ft::NodeTraits<value_type>::_tn_list_TS_Ptr nodePtr;

        typedef typename ft::MapIterator<value_type, value_compare> iterator;
        typedef typename ft::MapConstIterator<value_type, value_type const *, value_compare> const_iterator;
        typedef typename ft::ReverseIterator<iterator> reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;

        nodePtr _root;
        nodePtr _end;
        nodePtr _TNULL;
        allocator_type _alloc;
        std::allocator<typename ft::NodeTraits<value_type>::_tn_list_TS> _allocNode;
        value_compare _comp;
        size_type _size;


    public:
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        explicit RedBlackTree(const value_compare &compare, const allocator_type &alloc = allocator_type()) : _root(
                nullptr), _alloc(alloc), _comp(compare), _size(0) {
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

        RedBlackTree(const RedBlackTree& x) :   _alloc(x._alloc),
                                                _allocNode(x._allocNode),
                                                _comp(x._comp),
                                                _size(0) {
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

            for (const_iterator itBegin = x.begin(), itEnd = x.end(); itBegin != itEnd; ++itBegin) {
                insertUnique(*itBegin);
            }
        }

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------
        virtual ~RedBlackTree() {
            unlinkEndFromTree();
            clear();
            destroyAndDeallocateNode(_end);
            destroyAndDeallocateNode(_TNULL);
        }

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        RedBlackTree operator=(const RedBlackTree &x) {
            if (this != &x) {
                clear();
                for (iterator itBegin = x.begn(), itEnd = x.end(); itBegin != itEnd; ++itBegin) {
                    insertUnique(*itBegin);
                }
            }
        }

        // -----------------------------------------ITERATORS-----------------------------------------------------------

        iterator begin() {
            return iterator(_end->right);
        }

        iterator end() {
            return iterator(_end);
        }

        const_iterator begin() const {
            return const_iterator(_end->right);
        }

        const_iterator end() const {
            return const_iterator(_end);
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
            if (_end->left) {
                _end->left->right = _TNULL;
            }
        }

        void linkEndFromTree() {
            _end->left->right = _end;
        }

        void findMinimumInTree() {
            nodePtr tmp = _root;

            while (tmp->left != _TNULL) {
                tmp = tmp->left;
            }
            _end->right = tmp;
        }

        void findMaximumInTree() {
            nodePtr tmp = _root;

            while (tmp->right != _TNULL) {
                tmp = tmp->right;
            }
            _end->left = tmp;
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
            } else if (x == x->parent->right) {
                x->parent->right = y;
            } else {
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
            y->parent = x->parent;
            if (!x->parent) {
                _root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }

            // link x and y
            y->left = x;
            x->parent = y;
        }

        void insertFixup(nodePtr x) {
            // maintain red-black property after insertion
            nodePtr child;

            while (x->parent->color == RED) {
                // we have a violation
                if (x->parent == x->parent->parent->right) {
                    child = x->parent->parent->left;
                    if (child->color == RED) {
                        // uncle is RED
                        child->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    } else {
                        // uncle is BLACK
                        if (x == x->parent->left) {
                            // make x a right child
                            x = x->parent;
                            rotateRight(x);
                        }
                        // recolor and rotate
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotateLeft(x->parent->parent);
                    }
                } else {
                    // mirror image of above code
                    child = x->parent->parent->right;
                    if (child->color == RED) {
                        // uncle is RED
                        child->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    } else {
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
        std::pair<iterator, bool> insertUnique(const value_type &val) {
            unlinkEndFromTree();

            nodePtr y = nullptr, x = _root, newNode;

            while (x != _TNULL) {
                y = x;
                if (val.first == y->value_type.first) {
                    configureEndNode();
                    return std::make_pair(iterator(y), false);
                }
                x = _comp(val.first, x->value_type.first) ? x->left : x->right;
            }

            newNode = allocateNewNode(val, y);

            if (y == nullptr) {
                _root = newNode;
            } else if (_comp(newNode->value_type.first, y->value_type.first)) {
                y->left = newNode;
            } else {
                y->right = newNode;
            }

            if (!newNode->parent) {
                newNode->color = BLACK;
                configureEndNode();
                ++_size;
                return std::make_pair(iterator(newNode), true);
            }

            if (!newNode->parent->parent) {
                configureEndNode();
                ++_size;
                return std::make_pair(iterator(newNode), true);
            }

            insertFixup(newNode);
            configureEndNode();
            ++_size;
            return std::make_pair(iterator(newNode), true);
        }

        // -----------------------------------------Erase Elements------------------------------------------------------

    private:
        nodePtr findNode(nodePtr find) {
            nodePtr current = _root;
            while (current != _TNULL) {
                if (find == current) {
                    return current;
                }
                current = _comp(find->value_type.first, current->value_type.first) ? current->left : current->right;
            }
            return nullptr;
        }

        void rbTransplant(nodePtr u, nodePtr v) {
            if (!u->parent) {
                _root = v;
            } else if (u == u->parent->left) {
                u->parent->left = v;
            }
            else {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        nodePtr minimum(nodePtr node) {
            while (node->left != _TNULL) {
                node = node->left;
            }
            return node;
        }

        nodePtr maximum(nodePtr node) {
            while (node->right != _TNULL) {
                node = node->right;
            }
            return node;
        }

        void deleteFix(nodePtr x) {
            nodePtr s;
            while (x != _root && x->color == BLACK) {
                if (x == x->parent->left) {
                    s = x->parent->right;
                    if (s->color == RED) {
                        s->color = BLACK;
                        x->parent->color = RED;
                        rotateLeft(x->parent);
                        s = x->parent->right;
                    }

                    if (s->left->color == BLACK && s->right->color == BLACK) {
                        s->color = RED;
                        x = x->parent;
                    } else {
                        if (s->right->color == BLACK) {
                            s->left->color = BLACK;
                            s->color = RED;
                            rotateRight(s);
                            s = x->parent->right;
                        }

                        s->color = x->parent->color;
                        x->parent->color = BLACK;
                        s->right->color = BLACK;
                        rotateLeft(x->parent);
                        x = _root;
                    }
                } else {
                    s = x->parent->left;
                    if (s->color == RED) {
                        s->color = BLACK;
                        x->parent->color = RED;
                        rotateRight(x->parent);
                        s = x->parent->left;
                    }

                    if (s->right->color == BLACK && s->right->color == BLACK) {
                        s->color = RED;
                        x = x->parent;
                    } else {
                        if (s->left->color == BLACK) {
                            s->right->color = BLACK;
                            s->color = RED;
                            rotateLeft(s);
                            s = x->parent->left;
                        }

                        s->color = x->parent->color;
                        x->parent->color = BLACK;
                        s->left->color = BLACK;
                        rotateRight(x->parent);
                        x = _root;
                    }
                }
            }
            x->color = BLACK;
        }

    public:
        bool erase(const key_type &k) {

            unlinkEndFromTree();

            nodePtr z = _TNULL, x = nullptr, y = nullptr;

            if (!(z = findNodeKey(k))) {
                linkEndFromTree();
                return false;
            }

            y = z;
            nodeColor y_original_color = y->color;
            if (z->left == _TNULL) {
                x = z->right;
                rbTransplant(z, z->right);
            } else if (z->right == _TNULL) {
                z = z->left;
                rbTransplant(z, z->left);
            } else {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z) {
                    x->parent = y;
                } else {
                    rbTransplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                rbTransplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            destroyAndDeallocateNode(z);
            if (y_original_color == BLACK) {
                deleteFix(x);
            }
            configureEndNode();
            --_size;
            return true;
        }

        // -----------------------------------------Swap content--------------------------------------------------------

        void swap(RedBlackTree& x) {
            ft::swap(_root, x._root);
            ft::swap(_end, x._end);
            ft::swap(_TNULL, x._TNULL);
            ft::swap(_alloc, x._alloc);
            ft::swap(_allocNode, x._allocNode);
            ft::swap(_comp, x._comp);
            ft::swap(_size, x._size);
        }

        // -----------------------------------------Clear content-------------------------------------------------------

    private:
        void deleteRBTree(nodePtr root) {
           if (root != _TNULL) {
               deleteRBTree(root->left);
               deleteRBTree(root->right);
               destroyAndDeallocateNode(root);
           }
        }

    public:
        void clear() {
            deleteRBTree(_root);
        }

        // -----------------------------------------OBSERVERS-----------------------------------------------------------

        // -----------------------------------------Return Key Comparison Object----------------------------------------

        value_compare key_comp() const {
            return _comp;
        }

        // -----------------------------------------OPERATIONS----------------------------------------------------------

    private:
        nodePtr findNodeKey(const key_type &k) const {
            nodePtr current = _root;
            while (current != _TNULL) {
                if (k == current->value_type.first) {
                    return current;
                }
                current = _comp(k, current->value_type.first) ? current->left : current->right;
            }
            return nullptr;
        }

    public:
        iterator find(const key_type &k) {
            nodePtr findKey = findNodeKey(k);
            if (findKey)
                return iterator(findKey);
            return end();
        }

        const_iterator find(const key_type &k) const {
            nodePtr findKey = findNodeKey(k);
            if (findKey)
                return const_iterator(findKey);
            return end();
        }

        size_type count(const key_type& k) const {
            if (findNodeKey(k))
                return 1;
            return 0;
        }

        iterator lower_bound (const key_type& k) {
            nodePtr node = findNodeKey(k);
            if (node) {
                if ((node = findNode(node->left))) {
                    return iterator(node);
                }
            }
            return end();
        }



        const_iterator lower_bound (const key_type& k) const {
            nodePtr node = findNodeKey(k);
            if (node) {
                if ((node = findNode(node->left))) {
                    return iterator(node);
                }
            }
            return end();
        }

        iterator upper_bond(const key_type &k) {
            nodePtr node = findNodeKey(k);
            if (node) {
                iterator it = iterator(node);
                ++it;
                if ((node = findNodeKey(it->first))) {
                    return iterator(node);
                }
            }
            return end();
        }

        const_iterator upper_bond(const key_type &k) const {
            nodePtr node = findNodeKey(k);
            if (node) {
                const_iterator it = const_iterator(node);
                ++it;
                if ((node = findNode(it->first))) {
                    return const_iterator(node);
                }
            }
            return end();
        }

        std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
            return std::make_pair(lower_bound(k), upper_bond(k));
        }

        std::pair<iterator,iterator> equal_range(const key_type& k) {
            return std::make_pair(lower_bound(k), upper_bond(k));
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

        nodePtr allocateNewNode(const value_type &val, nodePtr parent) {
            nodePtr newNode = _allocNode.allocate(1);

            _alloc.construct(&newNode->value_type, val);
            newNode->parent = parent;
            newNode->left = _TNULL;
            newNode->right = _TNULL;
            newNode->color = RED;
            return newNode;
        }

        // -----------------------------------------Deallocate Memory---------------------------------------------------

        void destroyAndDeallocateNode(nodePtr node) {
            _alloc.destroy(&node->value_type);
            _allocNode.deallocate(node, 1);
        }
    };
}

#endif //REDBLACKTREE_H
