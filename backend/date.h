#pragma once
#include <string>

using namespace std;

struct Date
{
  int
      year,
      month,
      day;

  Date() : year(0), month(0), day(0) {}
  Date(string df);
  Date(int y, int m, int d) : year(y), month(m), day(d) {}
};

string to_string(Date d);
bool compare(Date a, Date b);