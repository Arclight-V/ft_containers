//
// Created by Arclight Natashia on 4/28/21.
//

#include "ft_list.h"
#include <vector>


void printModifeyIterator(ft::list<int> &printList) {

    // -----------------------------------------iterator ++itBegin------------------------------------------------------
    std::cout << "      iterator ++itBegin:";
    for (ft::list<int>::iterator itBegin = printList.begin(), itEnd = printList.end(); itBegin != itEnd; ++itBegin) {
        std::cout << ' ' << *itBegin;
    }
    std::cout << " \n";

    // -----------------------------------------iterator --itEnd--------------------------------------------------------
    std::cout << "      iterator   --itEnd:";
    ft::list<int>::iterator itEnd = --printList.end();
    for (ft::list<int>::iterator itBegin = printList.begin(); itBegin != itEnd; --itEnd) {
        std::cout << ' ' << *itEnd;
    }
    std::cout << ' ' << *itEnd;
    std::cout << "\n";
}

void printConstIterator(ft::list<int> &printList) {
    // -----------------------------------------const_iterator ++itBegin------------------------------------------------
    std::cout << "const_iterator ++itBegin:";
    for (ft::list<int>::const_iterator itBegin = printList.begin(), itEnd = printList.end(); itBegin != itEnd; ++itBegin) {
        std::cout << ' ' << *itBegin;
    }
    std::cout << "\n";


    // -----------------------------------------const_iterator --itEnd--------------------------------------------------
    std::cout << "const_iterator   --itEnd:";
    ft::list<int>::const_iterator itEnd = --printList.end();
    for (ft::list<int>::const_iterator itBegin = printList.begin(); itBegin != itEnd; --itEnd) {
        std::cout << ' ' << *itEnd;
    }
    std::cout << ' ' << *itEnd;
    std::cout << "\n";
}

//void printModifeyReverseIterator(ft::list<int> &printList) {
//    // -----------------------------------------iterator ++itBegin------------------------------------------------------
//    std::cout << "  reverse_iterator ++itBegin:";
//    for (ft::list<int>::reverse_iterator itBegin = printList.rbegin(), itEnd = printList.rend(); itBegin != itEnd; ++itBegin) {
//        std::cout << ' ' << *itBegin;
//    }
//    std::cout << " \n";
//
//    // -----------------------------------------iterator --itEnd--------------------------------------------------------
//    std::cout << "      iterator   --itEnd:";
//    ft::list<int>::iterator itEnd = --printList.end();
//    for (ft::list<int>::iterator itBegin = printList.begin(); itBegin != itEnd; --itEnd) {
//        std::cout << ' ' << *itEnd;
//    }
//    std::cout << ' ' << *itEnd;
//    std::cout << "\n";
//}

void printIterator(ft::list<int> &printList) {

    printModifeyIterator(printList);
    printConstIterator(printList);
//    printModifeyReverseIterator(printList);



}


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

void baseTestSplice () {
    ft::list<int> mylist1, mylist2;
    ft::list<int>::iterator it;

    // set some initial values:
    for (int i=1; i<=4; ++i)
        mylist1.push_back(i);      // mylist1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        mylist2.push_back(i*10);   // mylist2: 10 20 30

    it = mylist1.begin();
    ++it;                         // points to 2

    mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
    // mylist2 (empty)
    // "it" still points to 2 (the 5th element)

    it = mylist1.begin();
    ++it;

    for (int i=2; i<=4; ++i)
        mylist2.push_back(i*10);   // m
    mylist2.splice(++mylist2.begin(),mylist1, it);
    // mylist1: 1 10 20 30 3 4
    // mylist2: 2
    // "it" is now invalid

    printIterator(mylist1);
    printIterator(mylist2);
}

void testSplice() {
    baseTestSplice();
}

void baseTestInsert () {
    ft::list<int> mylist;
    ft::list<int>::iterator it;

    // set some initial values:
    for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5

    printIterator(mylist);

    it = mylist.begin();
    ++it;       // it points now to number 2           ^

    mylist.insert (it,10);                        // 1 10 2 3 4 5

    printIterator(mylist);
    // "it" still points to number 2                      ^
    mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5
    printIterator(mylist);
    --it;       // it points now to the second 20            ^

    std::vector<int> myvector (2,30);
    mylist.insert (it,myvector.begin(),myvector.end());
    // 1 10 20 30 30 20 2 3 4 5
    //               ^
    printIterator(mylist);
}
void testInsert()
{
    baseTestInsert();
}

void iteratorTest()
{
    BeginAndEndIteratorsAnEmptyContariner();
    goFromBeginToEnd();
    goFromEndToBegin();
//    testInsert();

    testResize();
    testSplice();

}


int main ()
{
    constructorTest();
    iteratorTest();
}



