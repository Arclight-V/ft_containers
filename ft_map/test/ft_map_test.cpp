//
// Created by Arclight Natashia on 5/27/21.
//

#include "../ft_map.h"
#include <iostream>
//#include <map>

int main () {


    ft::map<int, int> map1;

    map1.insert(std::pair<char,int>(55,55));
    map1.insert(std::pair<char,int>(40,40));
    map1.insert(std::pair<char,int>(65,65));
    map1.insert(std::pair<char,int>(60,60));
    map1.insert(std::pair<char,int>(75,75));
    map1.insert(std::pair<char,int>(57,57));

    ft::map<int, int>::iterator itBegin = map1.begin();
    std::cout << itBegin->first << '\n';

    ft::map<int, int>::iterator itEnd = map1.end();
    std::cout << itEnd->first << '\n';

    map1.printMap();


    return 0;
}
