//
// Created by Arclight Natashia on 4/28/21.
//

#include "ft_list.h"

void constructorTest()
{
//    ft::list<int> lst;
//    ft::list<const int> const lst1;
//    (void)lst;
//    (void)lst1;
}

/*
 *  go from the beginning to the end of the container
 */
void goFromBeginToEnd()
{

}

/*
 *  go from the ending to the begin of the container
 */
void goFromEndToBegin()
{

}


void BeginAndEndIteratorsAnEmptyContariner() {
    ft::list<int> lst;

//    lst.insert(lst.begin(), 10);
    std::list<int> lst2;
    for (int i = 0; i < 20; ++i) {
        lst2.push_back(i);
    }

    std::list<int>::reverse_iterator itBgin2 = lst2.rbegin();

    std::cout << itBgin2[2] << '\n';


    std::cout << *lst.begin() << '\n' << *lst.end();
//    for (ft::list<int>::iterator itBegin = lst.begin(); itBegin != lst.end(); itBegin++) {
//        std::cout << *itBegin << '\n';
//    }



//    std::cout << *lst.begin() << '\n';


}

void iteratorTest()
{
    BeginAndEndIteratorsAnEmptyContariner();
    goFromBeginToEnd();
    goFromEndToBegin();
}


int main ()
{
    constructorTest();
    iteratorTest();
}



