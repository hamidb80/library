#pragma once

#include <string>
#include <vector>
#include <locale>

using namespace std;
static vector<string> split(string s, char d)
{
  vector<string> res;
  int
      start = 0,
      i = 0;

  for (; i < s.length(); i++)
    if (s[i] == d)
    {
      res.push_back(s.substr(start, i - start));
      start = i + 1;
    }

  if (start != i)
    res.push_back(s.substr(start, i - start));

  return res;
}

static string s2lower(string s)
{
  for (char &c : s)
    c = tolower(c);
  return s;
}