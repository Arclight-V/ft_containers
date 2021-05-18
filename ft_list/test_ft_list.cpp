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
}

void testResize() {

    ft::list<int> mylist;
    std::list<int> stdList;

    // set some initial content:
    for (int i=1; i<10; ++i){
        mylist.push_back(i);
        stdList.push_back(i);
    }

    mylist.resize(5);
    stdList.resize(5);
//    mylist.resize(8,100);
//    mylist.resize(12);

    std::cout << " mylist contains:";
    for (ft::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';

    std::cout << "stdList contains:";
    for (std::list<int>::iterator it=stdList.begin(); it!=stdList.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';
}

void iteratorTest()
{
    BeginAndEndIteratorsAnEmptyContariner();
    goFromBeginToEnd();
    goFromEndToBegin();

    testResize();
}


int main ()
{
    constructorTest();
    iteratorTest();
}



