//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_STACK_H
#define FT_STACK_H

#include "../ft_list/ft_list.h"

namespace ft {

    template<class T, class Container = list <T> >
    class Stack {
    public:

        typedef T                                                       value_type;
        typedef Container                                               container_type;
        typedef size_t                                                  size_type;

    private:
        container_type                                                  _c;

        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

    public:
        explicit Stack(const container_type &container = container_type())
                : _c(container) {}

        Stack(const Stack &x)
                : _c(x._c) {}

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------

        ~Stack() {}

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        Stack &operator=(const Stack &x) {
            if (this == &x) {
                return *this;
            }
            _c = x._c;
            return *this;
        }

        // -----------------------------------------Test Whether Container Is Empty-------------------------------------

        bool empty() const {
            return _c.empty();
        }

        // -----------------------------------------Return Size---------------------------------------------------------

        size_type size() const {
            return _c.size();
        }

        // -----------------------------------------Access Next Element-------------------------------------------------

        value_type &top() {
            return _c.back();
        }

        value_type &top() const {
            return _c.back();
        }

        // -----------------------------------------Insert Element------------------------------------------------------

        void push(const value_type &val) {
            _c.push_back(val);
        }

        // -----------------------------------------Remove Top Element--------------------------------------------------

        void pop() {
            _c.pop_back();
        }
    };
    
        /*
        ** -----------------------------------------NON-MEMBER FUNCTIONS------------------------------------------------
        */

        // -----------------------------------------Relational Operators------------------------------------------------
    
        template<class T, class Container>
        bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
            return lhs._container == rhs._container;
        }

        template<class T, class Container>
        bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
            return lhs._container != rhs._container;
        }

        template<class T, class Container>
        bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
            return lhs._container < rhs._container;
        }

        template<class T, class Container>
        bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
         return lhs._container <= rhs._container;
        }

        template<class T, class Container>
        bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
            return lhs._container > rhs._container;
        }

        template<class T, class Container>
        bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
            return lhs._container >= rhs._container;
        }
}

#endif //FT_STACK_H
