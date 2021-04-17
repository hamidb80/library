#include "date.h"
#include "../common/str.hpp"

using namespace std;

string to_string(Date d)
{
  return (
      to_string(d.year) + "/" +
      to_string(d.month) + "/" +
      to_string(d.day));
}

Date::Date(string s)
{
  auto dl = split(s, '/');
  if (dl.size() != 3)
    throw "invalid date fotmat";

  try
  {
    year = stoi(dl[0]);
    month = stoi(dl[1]);
    day = stoi(dl[2]);
  }
  catch(...)
  {
    throw "invalid number";
  }
}

bool compare(Date a, Date b)
{
  int
      as[] = {a.year, a.month, a.day},
      bs[] = {b.year, b.month, b.day};

  for (int i = 0; i < 3; i++)
    if (as[i] < bs[i])
      return true;

  return false;
}