#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "../common/str.hpp"
using namespace std;


hash<string> hashFunc;
string getHash(string what)
{
  return to_string(hashFunc(what));
}

int main()
{
  auto ll = split("1/2/4", '/');
  for (int i = 0; i < ll.size(); i++)
    cout << ll[i] << endl;

  cout << getHash("1234");
}
