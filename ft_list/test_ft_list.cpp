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
    ft::list<int> mylist;
//  int sum (0);
  mylist.push_back (100);
  mylist.push_back (200);
  mylist.push_back (300);
  mylist.push_back (400);
  mylist.push_back (500);

  for (ft::list<int>::iterator itBegin = mylist.begin(), itEnd = mylist.end(); itBegin != itEnd; ++itBegin) {
        std::cout << *itBegin << ' ';
    }
  std::cout << '\n';
  mylist.erase(--mylist.end());

    for (ft::list<int>::iterator itBegin = mylist.begin(), itEnd = mylist.end(); itBegin != itEnd; ++itBegin) {
        std::cout << *itBegin << ' ';
    }
    std::cout << '\n';

  ft::list<int>::iterator itBegin = mylist.begin(), itEnd = --mylist.end();
  for (; itBegin != itEnd; --itEnd) {
        std::cout << *itEnd << ' ';
    }
  std::cout << *itEnd << ' ';
  std::cout << '\n';

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



