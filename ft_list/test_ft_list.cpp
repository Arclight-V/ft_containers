//
// Created by Arclight Natashia on 4/28/21.
//

#include "ft_list.h"

void constructorTest()
{
    ft::list<int> lst;
    ft::list<const int> const lst1;
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
    ft::list<int>::const_iterator itBeginConst = lst.begin();

//    ft::list<int>::const_iterator itBeginConst2 = lst2.begin();

//    itBeginConst = itBeginConst2;

//    itBeginMutable = itBeginMutable2;

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



