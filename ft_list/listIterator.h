//
// Created by Arclight Natashia on 5/4/21.
//

#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "stdafx.h"

// BIDIRECTIONAL ITERATOR

namespace ft {

    template<class Node>
    class ListIterator {

    public:
        // defining iterator trait types
        typedef typename std::iterator_traits<Node>::value_type         value_type;
        typedef typename std::iterator_traits<Node>::difference_type    difference_type;
        typedef typename std::iterator_traits<Node>::pointer            pointer;
        typedef typename std::iterator_traits<Node>::reference          reference;
        typedef typename std::bidirectional_iterator_tag                iterator_category;

        // Constructors
        ListIterator() : _node(nullptr) {};
        ListIterator(Node const &x) : _node(x._node) {};

        // Destructor
        virtual ~ListIterator() {};

    private:
        Node *_node;
    };
}

#endif //LISTITERATOR_H
