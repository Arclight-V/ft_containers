//
// Created by Arclight Natashia on 6/10/21.
//

#ifndef VECTORITERATOR_H
#define VECTORITERATOR_H

#include "../common_templates/baseIterator.h"
#include "ft_vector.h"
#include <vector>

// BIDIRECTIONAL ITERATOR
namespace ft {

    template<class T, class PointerT>
    class VectorIterator : public ft::baseIterator<std::random_access_iterator_tag, T > {

        template<typename, typename> friend class vector;

        typedef typename VectorIterator::pointer            pointer;
        typedef typename VectorIterator::reference          reference;
        typedef typename VectorIterator::difference_type    difference_type;

        pointer                                     _ptr;

    public:

        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

        // default-constructor
        explicit VectorIterator(pointer ptr = nullptr) : _ptr(ptr) {};

        // copy-constructor
        VectorIterator(VectorIterator<T, PointerT> const &x) : _ptr(x._ptr) {};

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------

        virtual ~VectorIterator() {};

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        VectorIterator &operator=(VectorIterator const &x) {
            if (this != &x) {
                _ptr = x._ptr;
            }
            return *this;
        }

        // Can be compared for equivalence using the equality/inequality operators
        // (meaningful when both iterator values iterate over the same underlying sequence)
        bool operator==(VectorIterator const &x) {
            return _ptr == x._ptr;
        }

        bool operator!=(VectorIterator const &x) {
            return _ptr != x._ptr;
        }

        // Can be dereferenced as an rvalue (if in a dereferenceable state)
        reference operator*() const {
            return *_ptr;
        }

        pointer operator->() const {
            return _ptr;
        }

        // Can be incremented (if in a dereferenceable state).
        // The result is either also dereferenceable or a past-the-end iterator.
        // Two iterators that compare equal, keep comparing equal after being both increased
        VectorIterator operator++() {
            _ptr++;
            return *this;
        }

        VectorIterator operator++(int) {
            VectorIterator ret(*this);
            _ptr++;
            return ret;
        }

        // Can be decremented (if a dereferenceable iterator value precedes it).
        VectorIterator operator--() {
            _ptr--;
            return *this;
        }

        VectorIterator operator--(int) {
            VectorIterator ret(*this);
            _ptr--;
            return ret;
        }

        VectorIterator operator+(difference_type n) const {
            return VectorIterator(_ptr + n);
        }

        VectorIterator operator-(difference_type n) const {
            return VectorIterator(_ptr - n);
        }

        VectorIterator operator-(VectorIterator b) const{
            return VectorIterator(_ptr - b);
        }

        reference operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }

        reference operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        reference operator[](difference_type index) {
            return _ptr[index];
        }

    };

    template <class Iter>
    bool operator<(Iter const &a, Iter const &b) {
        return *a._ptr < *b._ptr;
    }

    template <class Iter>
    bool operator>(Iter a, Iter b) {
        return !(a < b);
    }

    template <class Iter>
    bool operator<=(Iter a, Iter b) {
        return *a._ptr <= *b._ptr;
    }

    template <class Iter>
    bool operator>=(Iter a, Iter b) {
        return *a._ptr <= *b._ptr;
    }

}

#endif //VECTORITERATOR_H
