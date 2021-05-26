//
// Created by Arclight Natashia on 5/26/21.
//

#include <map>
#include <iostream>

int main () {

    std::map<char, std::string> map1;

    map1['a'] = "string1";
    map1['b'] = "string2";
    map1['b'] = "string3";

    std::map<char, std::string>::iterator itBegin = map1.begin();
//    std::string str2("test");
    *itBegin = std::pair< int, int>;
    std::cout << itBegin->second << '\n';
    return 0;
}
