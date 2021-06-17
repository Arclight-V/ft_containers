//
// Created by Arclight Natashia on 6/17/21.
//

#include <iostream>

#include "../ft_stack.h"

#define lib ft
#define con Stack

int main() {
    lib::con<int> def;

    std::cout << def.empty() << std::endl;
    std::cout << def.size() << std::endl;

    for (int i = 0; i < 10; ++i) {
        def.push(i);
    }

    std::cout << def.empty() << std::endl;
    std::cout << def.size() << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << def.top() << " ";
        def.pop();
    }

    std::cout << def.empty() << std::endl;
    std::cout << def.size() << std::endl;
    return 0;
}