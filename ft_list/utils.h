//
// Created by Arclight Natashia on 5/13/21.
//

#ifndef UTILS_H
#define UTILS_H

namespace ft {

    template <bool, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };
}


#endif //UTILS_H
