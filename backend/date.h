#pragma once

struct Date
{
  int
      year,
      month,
      day;

  Date() : year(0), month(0), day(0) {}
  Date(int y, int m, int d) : year(y), month(m), day(d) {}
};
