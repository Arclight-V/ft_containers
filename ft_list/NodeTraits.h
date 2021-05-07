//
// Created by Arclight Natashia on 5/7/21.
//

#ifndef NODETRAITS_H
#define NODETRAITS_H

namespace ft {
    template<typename T>
    struct NodeTraits {
        //  doubly-linked list T on the stack
        struct _dl_list_TS {
            T           value;
            _dl_list_TS *previous;
            _dl_list_TS *next;
        };

        //  doubly-linked list T on the heap
        struct _dl_list_TH {
            T           *value;
            _dl_list_TH *previous;
            _dl_list_TH *next;
        };
    };
}

#endif //NODETRAITS_H
