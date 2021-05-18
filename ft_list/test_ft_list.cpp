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
    return;
    ft::list<int> mylist;
    std::list<int> stdList;

    // set some initial content:
    for (int i=1; i<10; ++i){
        mylist.push_back(i);
        stdList.push_back(i);
    }

    mylist.resize(5);
    stdList.resize(5);
    mylist.resize(8,100);
    stdList.resize(8, 100);
    mylist.resize(12);
    stdList.resize(12);

    std::cout << " mylist contains:";
    for (ft::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';

    std::cout << "stdList contains:";
    for (std::list<int>::iterator it=stdList.begin(); it!=stdList.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';
}

void testSplice() {
    ft::list<int> mylist1, mylist2;
    ft::list<int>::iterator it;

    // set some initial values:
    for (int i=1; i<=4; ++i)
        mylist1.push_back(i);      // mylist1: 1 2 3 4

//    for (int i=1; i<=3; ++i)
//        mylist2.push_back(i*10);   // mylist2: 10 20 30

    it = mylist1.begin();
    ++it;                         // points to 2

    mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4

    std::cout << "myList conteins: ";
    for(ft::list<int>::iterator itBegin = mylist1.begin(), itEnd = mylist1.end(); itBegin != itEnd; ++itBegin) {
        std::cout << ' ' << *itBegin;
    }
    std::cout << '\n';

}

void iteratorTest()
{
    BeginAndEndIteratorsAnEmptyContariner();
    goFromBeginToEnd();
    goFromEndToBegin();

    testResize();
    testSplice();

}


int main ()
{
    constructorTest();
    iteratorTest();
}



