//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_MAP_H
#define FT_MAP_H

#include "../common_templates/stdafx.h"
#include "mapIterator.h"
#include "../common_templates/ReverseIterator.h"
#include "../common_templates/RedBlackTree.h"
#include "../common_templates/Algorithm.h"
#include "../common_templates/utils.h"


namespace ft {
    template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator < std::pair<const Key, T> > >
            class map {
    public:
        typedef Key                                                             key_type;
        typedef T                                                               mapped_type;
        typedef std::pair<const key_type, mapped_type>                          value_type;
        typedef Compare                                                         key_compare;
        typedef Alloc                                                           allocator_type;
        typedef typename allocator_type::reference                              reference;
        typedef typename allocator_type::const_reference                        const_reference;
        typedef typename allocator_type::pointer                                pointer;
        typedef typename allocator_type::const_pointer                          const_pointer;
        typedef typename allocator_type::size_type                              size_type;
        typedef typename allocator_type::size_type                              difference_type;

        typedef typename ft::MapIterator<value_type>                            iterator;
        typedef typename ft::MapConstIterator<value_type, value_type const *>   const_iterator;
        typedef typename ft::ReverseIterator<iterator>                          reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator>                    const_reverse_iterator;

    private:
        typedef ft::RedBlackTree<value_type, Compare, allocator_type>           RBTree;
        RBTree                                                                  _tree;

        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        // Empty container constructor (default constructor)
        // Constructs an empty container, with no elements.
    public:
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

        // Constructs a container with as many elements as the range [first,last),
        // with each element constructed from its corresponding element in that range.

//        template <class InputIterator>
//        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
//            ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) {
//            (void)isIter;
//
//        }

         // Copy constructor
         // Constructs a container with a copy of each of the elements in x.
//         map (const map& x) : _end(allocateMemoryForNode()),
//                              _comp(x._comp),
//                              _alloc(x.get_allocator()),
//                              _size(0) {
//
//        }

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------
//        virtual ~map() {
//            clear();
//            destroyAndDeallocateNode(_end);
//        }


        iterator begin() {
            return _tree.begin();
        };

        iterator end() {
            return _tree.end();
        }

         // c_it begin() const {};

        /*
         * Return iterator to end
         * Returns an iterator referring to the past-the-end element in the vector container.
         *
         * it end() {};
         * c_it end() const {};
         */

        /*
         * Return reverse iterator to reverse beginning
         * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
         *
         * rev_it rbegin();
         * c_rev_it rbegin() const;
         */

        /*
         * Return reverse iterator to reverse end
         * Returns a reverse iterator pointing to the theoretical element preceding the first element in the map container (which is considered its reverse end).
         *
         * rev_it rend();
         * c_rev_it rend() const;
         */

        // -----------------------------------------MODIFIERS-----------------------------------------------------------

        // -----------------------------------------Insert elements-----------------------------------------------------

        std::pair<iterator,bool> insert(const value_type& val) {
            return _tree.insertUnique(val);
        }
        /*
         * Relational operators
         *
         */
        /*
        template <class T, class Alloc>
        bool operator== (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs);

        template <class T, class Alloc>
        bool operator!= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs);

        template <class T, class Alloc>
        bool operator<  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs);

        template <class T, class Alloc>
        bool operator<= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs);

        template <class T, class Alloc>
        bool operator>  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs);

        template <class T, class Alloc>
        bool operator>= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs);
         *
         */

        // -----------------------------------------CAPACITY------------------------------------------------------------

         bool empty() const {
             return _tree.empty();
         }

         size_type size() const {
             return _tree.size();
         }

         size_type max_size() const {
             return _tree.max_size();
         }

        // -----------------------------------------ALLOCATOR-----------------------------------------------------------

        allocator_type get_allocator() const {
            return _tree.get_allocator();
        }


        /*
        ** -----------------------------------------AUXILIARY FUNCTIONS-------------------------------------------------
        */

        void printMap() {
            _tree.printTree();
        }

        // -----------------------------------------Allocate Memory-----------------------------------------------------

        // -----------------------------------------Deallocate Memory---------------------------------------------------
    };
}

#endif //FT_MAP_H
