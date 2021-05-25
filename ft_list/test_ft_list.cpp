//
// Created by Arclight Natashia on 4/28/21.
//

#include "ft_list.h"
#include <vector>
#include <list>
#include "test.hpp"

int main ()
{
    ft::list<Test> useless;
    std::cout << "empty() : " << useless.empty()    << std::endl;
    std::cout << "size    : " << useless.size()     << std::endl;

    std::list<Test> useless1;
    std::cout << "empty() : " << useless1.empty()    << std::endl;
    std::cout << "size    : " << useless1.size()     << std::endl;
}



