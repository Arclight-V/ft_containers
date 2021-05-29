//
// Created by Arclight Natashia on 5/27/21.
//

#include "../ft_map.h"
#include <iostream>
//#include <map>

int main () {


    ft::map<int, int> map1;

    std::srand(std::time(nullptr));

    for (int i = 0; i < 10; ++i) {
        int in = std::rand() % 100;
        std::cout << "in = " <<  in << '\n';
        map1.insert(std::pair<int,int>( in ,in));
    }


//    ft::map<int, int>::iterator itBegin = map1.begin();
//    std::cout << itBegin->first << '\n';
//
//    ft::map<int, int>::iterator itEnd = map1.end();
//    std::cout << itEnd->first << '\n';

    map1.printMap();


    return 0;
}
