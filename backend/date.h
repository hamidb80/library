#pragma once
#include <ctime>
#include <string>
#include "date.h"
#include "../utils/str.hpp"

using namespace std;

struct Date
{
  int
      year,
      month,
      day;

  Date() : year(0), month(0), day(0) {}
  Date(string s)
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
    catch (...)
    {
      throw "invalid number";
    }
  }
  Date(int y, int m, int d) : year(y), month(m), day(d) {}
  bool isNone()
  {
    return !(year || month || day);
  }
};

static string to_string(Date d)
{
  return (
      to_string(d.year) + "/" +
      to_string(d.month) + "/" +
      to_string(d.day));
}

static Date getNow()
{
  time_t t = time(0); // get time now
  struct tm *now = localtime(&t);
  return Date(
      now->tm_year + 1900,
      now->tm_mon + 1,
      now->tm_mday);
}

static bool compare(Date a, Date b)
{
  int
      as[] = {a.year, a.month, a.day},
      bs[] = {b.year, b.month, b.day};

  for (int i = 0; i < 3; i++)
    if (as[i] < bs[i])
      return true;

  return false;
}