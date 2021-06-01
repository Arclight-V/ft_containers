//
// Created by Arclight Natashia on 5/27/21.
//

#include "../ft_map.h"
#include <iostream>
//#include <map>

int main () {


    ft::map<int, int> map1;
    std::map<int, int> mapstd;

    std::srand(std::time(nullptr));


    for (int i = 0; i < 13; ++i) {
        int in = std::rand() % 100;
        map1.insert(std::pair<int,int>( in ,in));
        mapstd.insert(std::pair<int,int>( in ,in));
    }


    map1.printMap();

    std::map<int, int>::iterator itBeginStd = mapstd.begin(), itEndStd = mapstd.end();
    std::cout << "std =";
    for (; itBeginStd != itEndStd; ++itBeginStd) {
        std::cout << " ";
        std::cout << itBeginStd->first;
    }
    std::cout << '\n';
//
//
    ft::map<int, int>::iterator itBegin = map1.begin(), itEnd = map1.end();
    std::cout << "mym =";
    for (int i = 0 ;itBegin != itEnd && i < 13; ++itBegin, ++i) {

        std::cout << " ";
        std::cout << itBegin->first;

    }
    std::cout << '\n';

    itBegin = map1.begin(), itEnd = map1.end();
    std::cout << "mym =";
    for (int i = 0 ;itEnd != itBegin && i < 13; --itEnd, ++i ) {

        std::cout << " ";
        std::cout << itEnd->first;

    }
    std::cout << '\n';



    return 0;
}
