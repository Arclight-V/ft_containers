//
// Created by Arclight Natashia on 5/18/21.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace ft {
    template<class T>
    void swap(T &a, T &b) {
        T tmp;
        tmp = a;
        a = b;
        b = tmp;
    }

    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
        while (first1 != last1) {
            if (!(*first1 == *first2)) // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template<class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <class RandIter>
    typename std::iterator_traits<RandIter>::difference_type
    __distance(RandIter first, RandIter last, std::random_access_iterator_tag)
    {
        return last - first;
    }

    template <class InputIterator>
    typename std::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
        return __distance(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
    }


    // -----------------------------------------Compare binary predicate------------------------------------------------

    template<class T>
    struct less {
    public:
        bool
        operator()(const T &lhs, const T &rhs) const {
            return (lhs < rhs);
        }
    };

    template<class T>
    struct equalTo {
    public:
        bool
        operator()(const T &lhs, const T &rhs) const {
            return (lhs == rhs);
        }
    };
}

#endif //ALGORITHM_H
