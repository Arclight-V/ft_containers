//
// Created by Arclight Natashia on 5/9/21.
//

#ifndef REVERSEITERATOR_H
#define REVERSEITERATOR_H

#include "baseIterator.h"

template<class Iterator>
class ReverseIterator : public ft::baseIterator<typename std::iterator_traits<Iter>::iterator_category,
        typename std::iterator_traits<Iter>::value_type,
        typename std::iterator_traits<Iter>::difference_type,
        typename std::iterator_traits<Iter>::pointer,
        typename std::iterator_traits<Iter>::reference> {

private:
    Iterator _iterator;
public:

    typedef Iterator                iterator_type;


    -----------------------------------------
    /*
    ** -----------------------------------------CONSTRUCTOR-------------------------------------------------------------
    */

    ReverseIterator() : _iterator();

    explicit ReverseIterator(Iter x) : _iterator(x) {};

    ReverseIterator(ReverseIterator<Iterator> const &x) : _iterator(x._iterator) {};

    /*
    ** -----------------------------------------DESTRUCTOR--------------------------------------------------------------
    */

    virtual ~ReverseIterator() {};

    /*
    ** -----------------------------------------MEMBER FUNCTIONS--------------------------------------------------------
    */

    ReverseIterator &operator=(ReverseIterator const &x) {
        if (this != x) {
            _iterator = x;
        }
        return *this;
    }

    iterator_type base() const {
        return _iterator;
    }

    typename ReverseIterator::reference operator*() const {
        return *(--_iterator);
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
        return ReverseIterator<_iterator - n>;
    }

    ReverseIterator &operator+=(difference_type n) {
        _iterator -= n;
        return *this;
    }

    ReverseIterator operator-(difference_type n) const {
        return ReverseIterator<_iterator + n>;
    }

    ReverseIterator &operator-=(difference_type n) {
        _iterator += n;
        return *this;
    }

    typename ReverseIterator::reference operator[](difference_type n) const {
        return *(*this + n);
    }
}
    /*
    ** -----------------------------------------NON-MEMBER FUNCTIONS OVERLOADS------------------------------------------
    */

    template <class Iterator>
    bool operator==(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
        return lhs.base() != rhs.base();
    }

    template <class Iterator>
    bool operator<(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
        return lhs.base() > rhs.base();
    }

    template <class Iterator>
    bool operator<=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template <class Iterator>
    bool operator>  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
        return lhs.base() < rhs.base();
    }

    template <class Iterator>
    bool operator>= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+ ( typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator>& rev_it) {
        return ReverseIterator<rev_it - n>;
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() - lhs.base();
}


#endif //REVERSEITERATOR_H
