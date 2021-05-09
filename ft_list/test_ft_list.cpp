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

    for (int i = 1; i < 10; ++i) {
        lst.push_back(i);
    }
    for (ft::list<int>::iterator itBegin = lst.begin(); itBegin != lst.end(); ++itBegin) {
        std::cout << *itBegin << '\n';
    }

    lst.erase(lst.begin());

    for (ft::list<int>::iterator itBegin = lst.begin(); itBegin != lst.end(); ++itBegin) {
        std::cout << *itBegin << '\n';
    }




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



