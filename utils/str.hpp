#pragma onces

#include <string>
#include <vector>
using namespace std;

vector<string> split(string s, char d)
{
  vector<string> res;
  int
      start = 0,
      i = 0;

  for (; i < s.length(); i++)
    if (s[i] == d)
    {
      res.push_back(s.substr(start, i - start));
      start = i+1;
    }

  if (start != i)
    res.push_back(s.substr(start, i - start));

  return res;
}
