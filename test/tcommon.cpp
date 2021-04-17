#include <iostream>
#include "../common/str.hpp"
using namespace std;

int main(){
  auto ll = split("1/2/4", '/');
  for (int i = 0; i < ll.size(); i++)
    cout << ll[i]<< endl;
}