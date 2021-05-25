//
// Created by Arclight Natashia on 4/28/21.
//

#include "ft_list.h"
#include <vector>
#include <list>
#include "test.hpp"

int main ()
{
    ft::list<int> mylist;

    for (int i=1; i<10; ++i) mylist.push_back(i);

    mylist.reverse();

    std::cout << "mylist contains:";
    for (ft::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';
}



