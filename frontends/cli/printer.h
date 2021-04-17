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

string getLine(string promptText = "")
{
  cout << promptText;
  string inp;
  getline(cin, inp);
  return inp;
}

string repeat(char ch, int num)
{
  string res;
  for (int i = 0; i < num; i++)
    res += ch;

  return res;
}

string indent(int num)
{
  return repeat(' ', num);
}

void printMessage(string header, string text, string fore = "bright white")
{
  // -------- Header -------
  // message
  // -----------------------

  int tlen = min(static_cast<int>(text.length()), 40);
  if (tlen % 2 == 1)
    tlen++;

  int r = (tlen - header.length()) / 2;
  cout << endl
       << hue::yellow_on_grey << repeat('-', r) << ' ' << header << ' ' << repeat('-', r) << hue::reset << endl
       << dye::colorize(text, fore) << endl
       << hue::yellow_on_grey << repeat('-', tlen + 2) << hue::reset << endl;
}
void print_err(string err)
{
  printMessage("Error", err, "red");
}
void print_success(string text)
{
  printMessage("Info", text, "green");
}

void print_info(string text)
{
  printMessage("Info", text, "aqua");
}