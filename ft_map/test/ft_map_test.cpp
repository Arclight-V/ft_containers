//
// Created by Arclight Natashia on 5/27/21.
//

//#include "../ft_map.h"
#include <iostream>
#include <map>

int main () {

//    ft::map<char, std::string> map1;
//
//    std::cout << map1.size() << '\n';
//    std::cout << map1.empty() << '\n';
//    std::cout << map1.max_size() << '\n';
//

    std::map<char, std::string> map1;
    map['a'] = "test";

    std::map<char, std::string>::iterator itBegin = map1.begin();

    --itBegin;

    std::cout << itBegin->first << '\n';


    return 0;
}
