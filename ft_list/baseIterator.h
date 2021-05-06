//
// Created by Arclight Natashia on 5/6/21.
//

#ifndef BASEITERATOR_H
#define BASEITERATOR_H

namespace ft {
    template<typename Category, typename T, typename Difference = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&>
    struct baseIterator {
        typedef T value_type;
        typedef Difference difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };
}

#endif //BASEITERATOR_H
