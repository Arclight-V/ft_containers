//
// Created by Arclight Natashia on 5/9/21.
//

#ifndef REVERSEITERATOR_H
#define REVERSEITERATOR_H

#include "baseIterator.h"

namespace ft {
    template<class Iterator>
    class ReverseIterator : public ft::baseIterator<typename std::iterator_traits<Iterator>::iterator_category,
                                                    typename std::iterator_traits<Iterator>::value_type,
                                                    typename std::iterator_traits<Iterator>::difference_type,
                                                    typename std::iterator_traits<Iterator>::pointer,
                                                    typename std::iterator_traits<Iterator>::reference> {
    public:
        typedef Iterator iterator_type;
        typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename std::iterator_traits<Iterator>::reference reference;
        typedef typename std::iterator_traits<Iterator>::pointer pointer;

        /*
        ** -----------------------------------------CONSTRUCTOR---------------------------------------------------------
        */

        ReverseIterator() : _iterator() {};

        explicit ReverseIterator(Iterator x) : _iterator(x) {};

        ReverseIterator(ReverseIterator<Iterator> const &x) : _iterator(x._iterator) {};

        /*
        ** -----------------------------------------DESTRUCTOR----------------------------------------------------------
        */

        virtual ~ReverseIterator() {};

        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */

        ReverseIterator &operator=(ReverseIterator const &x) {
                _iterator = x.base();
            return *this;
        }

        iterator_type base() const {
            return _iterator;
        }

        typename ReverseIterator::reference operator*() const {
            Iterator tmp = _iterator;
            return *--tmp;
        }

        typename ReverseIterator::pointer operator->() const {
            return &(operator*());
        }

        ReverseIterator &operator++() {
            --_iterator;
            return *this;
        }

        ReverseIterator operator++(int) {
            ReverseIterator ret(*this);
            --_iterator;
            return ret;
        }

        ReverseIterator &operator--() {
            ++_iterator;
            return *this;
        }

        ReverseIterator operator--(int) {
            ReverseIterator ret(*this);
            ++_iterator;
            return ret;
        }

        ReverseIterator operator+(difference_type n) const {
            return ReverseIterator(_iterator - n);
        }

        ReverseIterator &operator+=(difference_type n) {
            _iterator -= n;
            return *this;
        }

        ReverseIterator operator-(difference_type n) const {
            return ReverseIterator(_iterator + n);
        }

        ReverseIterator &operator-=(difference_type n) {
            _iterator += n;
            return *this;
        }

        typename ReverseIterator::reference operator[](difference_type n) const {
            return *(*this + n);
        }
    private:
        iterator_type _iterator;
    };

    /*
    ** -----------------------------------------NON-MEMBER FUNCTIONS OVERLOADS------------------------------------------
    */

    template<class Iterator>
    bool operator==(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<class Iterator>
    bool operator!=(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<class Iterator>
    bool operator<(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<class Iterator>
    bool operator<=(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<class Iterator>
    bool operator>(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<class Iterator>
    bool operator>=(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class Iterator>
    ReverseIterator<Iterator>operator+(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator> &rev_it) {
        return ReverseIterator<Iterator>(rev_it - n);
    }

    template<class Iterator>
    typename ReverseIterator<Iterator>::difference_type
    operator-(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs) {
        return rhs.base() - lhs.base();
    }
}

#endif //REVERSEITERATOR_H
