#pragma once
#include <string>

#include "color.hpp"
using namespace std;

template <typename T>
T getInput(string promptText = "", bool ignore_rest = true)
{
  T inp;
  cout << promptText;
  cin >> inp;

  if (ignore_rest)
  {
    cin.clear();
    cin.ignore(1);
  }

  return inp;
}

string repeat(char ch, int num)
{
  string res;
  for (int i = 0; i < num; i++)
    res += ch;

  return res;
}

void printMessage(string header, string text, string color)
{
  // -------- Header -------
  // message
  // -----------------------

  int tlen = min(static_cast<int>(text.length()), 40);
  if (tlen % 2 == 1)
    tlen++;

  int r = (tlen - header.length()) / 2;

  cout << endl
       << repeat('-', r) << ' ' << header << ' ' << repeat('-', r) << endl
       << dye::colorize(text, color) << endl
       << repeat('-', tlen + 2) << endl
       << endl;
}
void print_err(string err)
{
  printMessage("Error", err, "red");
}
void print_success(string text)
{
  printMessage("", text, "green");
}

void print_info(string text)
{
  printMessage("Info", text, "aqua");
}