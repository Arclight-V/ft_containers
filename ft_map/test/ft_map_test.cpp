//
// Created by Arclight Natashia on 5/27/21.
//

#include "../ft_map.h"
#include <iostream>
//#include <map>

int main () {


    ft::map<char, int> map1;

    map1.insert(std::pair<char,int>('a',55));
    map1.insert(std::pair<char,int>('b',40));
    map1.insert(std::pair<char,int>('c',65));
    map1.insert(std::pair<char,int>('z',60));
    map1.insert(std::pair<char,int>('d',75));
    map1.insert(std::pair<char,int>('g',57));

    ft::map<char, int>::iterator itBegin = map1.begin();
    std::cout << itBegin->first << '\n';


    return 0;
}
