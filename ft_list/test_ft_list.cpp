//
// Created by Arclight Natashia on 4/28/21.
//

#include "ft_list.h"
#include <vector>
#include <list>

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
    mylist1.clear();
    mylist2.clear();

    for (int i=1; i<=4; ++i)
        mylist1.push_back(i);      // mylist1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        mylist2.push_back(i*10);   // mylist2: 10 20 30



    // mylist2 (empty)
    // "it" still points to 2 (the 5th element)

    mylist2.splice (mylist2.begin(),mylist1, it);
    // mylist1: 1 10 20 30 3 4
    // mylist2: 2
    // "it" is now invalid.
//    it = mylist1.begin();
//    std::advance(it,3);           // "it" points now to 30

    it = mylist2.begin();
    ++it;                         // points to 2

//    mylist1.splice( mylist1.begin(), mylist2, it, mylist2.end());
    // mylist1: 30 3 4 1 10 20

    std::cout << "mylist1 contains:";
    for (it=mylist1.begin(); it!=mylist1.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "mylist2 contains:";
    for (it=mylist2.begin(); it!=mylist2.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

//    printIterator(mylist1);
//    printIterator(mylist2);
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

void baseTestRemove() {
    int myints[]= {17,89,7,14, 89, 3, 44,89,89};
    ft::list<int> mylist (myints,myints+8);

    mylist.remove(89);

    std::cout << "mylist contains:";
    for (ft::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void testRemove() {

    baseTestRemove();
}


void iteratorTest()
{
    BeginAndEndIteratorsAnEmptyContariner();
    goFromBeginToEnd();
    goFromEndToBegin();
//    testInsert();

    testResize();
//    testSplice();
    testRemove();

}


int main ()
{
    constructorTest();
    iteratorTest();
}



