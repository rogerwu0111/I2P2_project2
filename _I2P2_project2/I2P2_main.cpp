#include <iostream>
#include "header/I2P2_def.h"
#include "header/I2P2_container.h"
#include "header/I2P2_iterator.h"
#include "header/I2P2_List.h"

void print(I2P2::List &lst){
  for (I2P2::iterator it = lst.begin(); it != lst.end(); ++it){
  std::cout << *it << ' ';
  }
  std::cout << '\n';
}

int main(){

    using value_type = double;
    
    I2P2::List lst;

    lst.insert(lst.begin(), 3, 200);

    //print(lst);

    lst.insert(lst.begin(), lst.begin(), lst.end());

    //print(lst);

    lst.push_front(100);

    //I2P2::iterator x = lst.begin();

    //std::cout << *x << '\n';

    //print(lst);

    lst.erase(lst.begin()+3);

    //print(lst);

    lst.erase(lst.begin(), lst.begin()+2);

    //print(lst);

    lst.push_back(300);

    //print(lst);

    lst.pop_front();

    //print(lst);

    lst.pop_back();

    //print(lst);

    I2P2::List lst2 = lst;

    lst2.clear();

    lst2.push_back(100);

    //print(lst2);

    std::cout << lst.front() << '\n';

    std::cout << "Finish" <<std::endl;
}

/* vector : g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DDOUBLE -std=c++11
    list : g++ I2P2_main.cpp src/*.cpp -DTEST_LIST -DDOUBLE -std=c++11 */