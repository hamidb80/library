#pragma once
#include <string>
using namespace std;

template <typename T>
T getInput(string promptText = "")
{
  T inp;
  cout << promptText;
  cin >> inp;
  return inp;
}
