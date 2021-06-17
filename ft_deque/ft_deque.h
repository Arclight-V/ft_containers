//
// Created by Arclight Natashia on 4/28/21.
//

#ifndef FT_DEQUE_H
#define FT_DEQUE_H

#include "../ft_list/ft_list.h"

namespace ft {

    template<class T, class Container = List <T> >
    class Queue {
    public:
        typedef T                                           value_type;
        typedef Container                                   container_type;
        typedef size_t                                      size_type;

    private:
        container_type                                      _c;

        /*
        ** -----------------------------------------MEMBER FUNCTIONS----------------------------------------------------
        */
        // -----------------------------------------CONSTRUCTORS--------------------------------------------------------

    public:
        explicit Queue(const container_type &container = container_type())
                : _c(container) {}

        Queue(const Queue &x)
                : _c(x._c) {}

        // -----------------------------------------DESTRUCTOR----------------------------------------------------------

        ~Queue() {}

        // -----------------------------------------ASSIGN CONTENT------------------------------------------------------

        Queue &operator=(const Queue &x) {
            if (this == &x) {
                return *this;
            }
            _c = x._c;
            return *this;
        }

        // -----------------------------------------Test Whether Container Is Empty-------------------------------------

        bool empty() const {

            return this->_c.empty();
        }

        // -----------------------------------------Return Size---------------------------------------------------------

        size_type size() const {

            return this->_c.size();
        }

        // -----------------------------------------Access Next Element-------------------------------------------------

        value_type &front() {

            return this->_c.front();
        }

        const value_type &front() const {

            return this->_c.front();
        }

        // -----------------------------------------Access Last Element-------------------------------------------------

        value_type &back() {

            return this->_c.back();
        }

        const value_type &back() const {

            return this->_c.back();
        }

        // -----------------------------------------Insert Element------------------------------------------------------

        void push(const value_type &val) {

            return this->_c.push_back(val);
        }

        // -----------------------------------------Remove Next Element-------------------------------------------------

        void pop() {

            return this->_c.pop_front();
        }


        container_type getContainerType() const {

            return this->_c;
        }
    };

    /*
    ** -----------------------------------------NON-MEMBER FUNCTIONS------------------------------------------------
    */

    // -----------------------------------------Relational Operators------------------------------------------------

    template<class T, class Container>
    bool operator==(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {

        return lhs.getContainerType() == rhs.getContainerType();
    }

    template<class T, class Container>
    bool operator!=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {

        return lhs.getContainerType() != rhs.getContainerType();
    }

    template<class T, class Container>
    bool operator<(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {

        return lhs.getContainerType() < rhs.getContainerType();
    }

    template<class T, class Container>
    bool operator<=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {

        return lhs.getContainerType() <= rhs.getContainerType();
    }

    template<class T, class Container>
    bool operator>(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {

        return lhs.getContainerType() > rhs.getContainerType();
    }

    template<class T, class Container>
    bool operator>=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {

        return lhs.getContainerType() >= rhs.getContainerType();
    }
}

#endif //FT_DEQUE_H
