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
    ft::list<int> first;
    ft::list<int> second;

    first.assign (7,100);                      // 7 ints with value 100

    second.assign (first.begin(),first.end()); // a copy of first

    int myints[]={1776,7,4};
    first.assign (myints,myints+3);            // assigning from array

    std::cout << "Size of first: " << int (first.size()) << '\n';
    std::cout << "Size of second: " << int (second.size()) << '\n';
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



