//
// Created by Arclight Natashia on 5/27/21.
//

#include "../ft_map.h"
#include <iostream>

int main () {

    ft::map<char, std::string> map1;

    std::cout << map1.size() << '\n';
    std::cout << map1.empty() << '\n';
    std::cout << map1.max_size() << '\n';

    return 0;
}
