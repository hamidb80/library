#include <string>
using namespace std;

struct Sort
{
  string by;
  bool asc;

  Sort(string _by, bool _asc): by(_by), asc(_asc) {}
};
