//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_MULTISET_H
#define FT_MULTISET_H

#include "../common_templates/stdafx.h"
#include "MultisetIterator.h"
#include "../common_templates/ReverseIterator.h"
#include "../common_templates/Algorithm.h"
#include "RedBlackTreeMultiSet.h"
#include "../common_templates/utils.h"
#include <set>

namespace ft {

template < class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
        class multiset {

        public:
            typedef T                                                                           key_type;
            typedef T                                                                           value_type;
            typedef Compare                                                                     key_compare;
//            typedef Compare                                                                     value_compare;
            typedef Alloc                                                                       allocator_type;
            typedef typename allocator_type::reference                                          reference;
            typedef typename allocator_type::const_reference                                    const_reference;
            typedef typename allocator_type::pointer                                            pointer;
            typedef typename allocator_type::const_pointer                                      const_pointer;
            typedef typename allocator_type::size_type                                          size_type;
            typedef typename allocator_type::size_type                                          difference_type;

            typedef typename ft::MultisetIterator<value_type, key_compare>                           iterator;
            typedef typename ft::MultisetConstIterator<value_type, value_type const *, key_compare>  const_iterator;
            typedef typename ft::ReverseIterator<iterator>                                      reverse_iterator;
            typedef typename ft::ReverseIterator<const_iterator>                                const_reverse_iterator;

            class value_compare
            {
                friend class multiset;
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
            typedef ft::RedBlackTreeMultiSeT<key_type, value_type, Compare, allocator_type>     RBTree;
            RBTree                                                                              _tree;

            /*
            ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
            */
            // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        public:
            explicit multiset(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

            // Constructs a container with as many elements as the range [first,last),
            // with each element constructed from its corresponding element in that range.

            template <class InputIterator>
            multiset(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type isIter = InputIterator()) : _tree(comp, alloc) {
                (void)isIter;

                for (; first != last; ++first) {
                    _tree.insertMulti(*first);
                }
            }

            // Copy constructor
            // Constructs a container with a copy of each of the elements in x.
            multiset (const multiset& x) : _tree(x._tree) {
            }

            // -----------------------------------------DESTRUCTOR----------------------------------------------------------
            virtual ~multiset() {
            }

            // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

            multiset operator=(const multiset &x) {
                _tree = x._tree;
                return *this;
            }

            // -----------------------------------------ITERATORS-----------------------------------------------------------

            iterator begin() {
                return _tree.begin();
            }

            iterator end() {
                return _tree.end();
            }

            const_iterator begin() const {
                return _tree.begin();
            }

            const_iterator end() const {
                return _tree.end();
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

            // -----------------------------------------MODIFIERS-----------------------------------------------------------

            // -----------------------------------------Insert elements-----------------------------------------------------

            iterator insert(const value_type& val) {
                return _tree.insertMulti(val);
            }

            iterator insert(iterator position, const value_type& val) {
                (void)position;
                return insert(val);
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
                _tree.erase(position._node->value_type);
            }

            size_type erase(const key_type& k) {
                size_type num = 0;

                while(_tree.erase(k))
                    ++num;
                return num;
            }

            void erase(iterator first, iterator last) {
                while(first != last) {
                    _tree.erase((first++)._node->value_type);
                }
            }

            // -----------------------------------------Swap Content--------------------------------------------------------

            void swap(multiset& x) {
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
            iterator lower_bound(const key_type& k) {
                return _tree.lower_bound(k);
            }

            const_iterator lower_bound(const key_type& k) const {
                return _tree.lower_bond(k);
            }

            iterator upper_bound(const key_type& k) {
                return _tree.upper_bond(k);
            }

            const_iterator upper_bound(const key_type& k) const {
                return _tree.upper_bond(k);
            }

            std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
                return _tree.equal_range(k);
            }

            std::pair<iterator,iterator> equal_range(const key_type& k) {
                return _tree.equal_range(k);
            }

            // -----------------------------------------ALLOCATOR-----------------------------------------------------------

            allocator_type get_allocator() const {
                return _tree.get_allocator();
            }
        };
}


#endif //FT_MULTISET_H
