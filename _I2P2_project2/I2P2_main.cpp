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
  std::cout << lst.size() << '\n';
}

int main(){

    using value_type = double;
    
    I2P2::List lst;

    lst.insert(lst.begin(), 1, 200);

    lst.push_back(300);

    lst.push_front(100);

    lst.insert(lst.begin(), lst.begin(), lst.end());

    lst.erase(lst.begin()+3);

    lst.insert(lst.begin(), lst.begin(), lst.end());

    lst.erase(lst.begin()+2, lst.begin()+8);

    lst.insert(lst.begin(), 5, 100);

    print(lst);

    std::cout << "Finish" <<std::endl;
}

/* vector : g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DDOUBLE -std=c++11
    list : g++ I2P2_main.cpp src/*.cpp -DTEST_LIST -DDOUBLE -std=c++11 */