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
        typedef Key                                                                         key_type;
        typedef T                                                                           mapped_type;
        typedef std::pair<const key_type, mapped_type>                                      value_type;
        typedef Compare                                                                     key_compare;
        typedef Alloc                                                                       allocator_type;
        typedef typename allocator_type::reference                                          reference;
        typedef typename allocator_type::const_reference                                    const_reference;
        typedef typename allocator_type::pointer                                            pointer;
        typedef typename allocator_type::const_pointer                                      const_pointer;
        typedef typename allocator_type::size_type                                          size_type;
        typedef typename allocator_type::size_type                                          difference_type;

        typedef typename ft::MapIterator<value_type, key_compare>                           iterator;
        typedef typename ft::MapConstIterator<value_type, value_type const *, key_compare>  const_iterator;
        typedef typename ft::ReverseIterator<iterator>                                      reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator>                                const_reverse_iterator;

        class value_compare
        {
            friend class map;
        protected:
            key_compare comp;
            value_compare (Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            bool operator() (const value_type& x, const value_type& y) const {
                return comp(x.first, y.first);
            }
        };

    private:
        typedef ft::RedBlackTree<key_type, value_type, Compare, allocator_type>             RBTree;
        RBTree                                                                              _tree;


//        class value_compare : public std::binary_function<value_type, value_type, bool>
//        {
//            friend class RedBlackTree;
//        protected:
//            Compare comp;
//            value_compare(Compare c) : comp(c) {}
//        public:
//            bool operator() (const value_type& x, const value_type& y) const
//            {
//                return comp(x.first, y.first);
//            }
//        };

        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

    public:
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

        // Constructs a container with as many elements as the range [first,last),
        // with each element constructed from its corresponding element in that range.

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) : _tree(comp, alloc) {
            (void)isIter;

            for (; first != last; ++first) {
                _tree.insertUnique(*first);
            }
        }

         // Copy constructor
         // Constructs a container with a copy of each of the elements in x.
         map (const map& x) : _tree(x._tree) {
        }

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------
        virtual ~map() {
        }

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        map operator=(const map &x) {
            _tree = x._tree;
        }

        // -----------------------------------------ITERATORS-----------------------------------------------------------

        iterator begin() {
            return _tree.begin();
        }

        iterator end() {
            return _tree.end();
        }

        const_iterator begin() const {
            return const_iterator(_tree.cbegin());
        }

        const_iterator end() const {
            return const_iterator(_tree.cend());
        }

        reverse_iterator  rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

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

        // -----------------------------------------ELEMENT ACCESS------------------------------------------------------

        mapped_type& operator[] (const key_type& k) {
            (*((this->insert(make_pair(k,mapped_type()))).first)).second;
        }

        // -----------------------------------------MODIFIERS-----------------------------------------------------------

        // -----------------------------------------Insert elements-----------------------------------------------------

        std::pair<iterator,bool> insert(const value_type& val) {
            return _tree.insertUnique(val);
        }

        iterator insert(iterator position, const value_type& val) {
            (void)position;
            return _tree.isertUnique(val);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last, typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) {
            (void)isIter;

            for (; first != last; ++first) {
                insert(*first);
            }

        }

        // -----------------------------------------Erase Elements------------------------------------------------------

        void erase(iterator position) {
            _tree.erase(position->first);
        }

        size_type erase(const key_type& k) {
            _tree.erase(k);
            return 1;
        }

        void erase(iterator first, iterator last) {
            while(first != last) {
                _tree.erase(first->first);
            }
        }

        // -----------------------------------------Swap Content--------------------------------------------------------

        void swap(map& x) {
            _tree.swap(x._tree);
        }

        // -----------------------------------------Clear Content-------------------------------------------------------

        void clear() {
            _tree.clear();
        }

        // -----------------------------------------OBSERVERS-----------------------------------------------------------

        // -----------------------------------------Return Key Comparison Object----------------------------------------

        key_compare key_comp() const {
            return _tree.key_comp();
        }

        // -----------------------------------------Return value Comparison Object----------------------------------------

        value_compare value_comp() const {
            return _tree.value_comp();
        }


        // -----------------------------------------OPERATIONS----------------------------------------------------------

        iterator find(const key_type& k) {
            return _tree.find(k);
        }

        const_iterator find(const key_type& k) const {
            return _tree.find(k);
        }

        size_type count(const key_type& k) const {
            return _tree.count(k);
        }

//        const_iterator find (const key_type& k) const {
//
//        }
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
