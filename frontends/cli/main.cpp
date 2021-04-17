#include <iostream>
#include <vector>

// https://github.com/nlohmann/json

#include "../../backend/date.h"
#include "../../backend/admin.h"
#include "../../backend/user.h"
#include "../../backend/book.h"
#include "../../backend/borrowing.h"
#include "utils.h"

using namespace std;

int main()
{
  cout
      << "1. login/logout" << endl
      << "2. show/search books" << endl
      << "3. book status" << endl
      << "4. borrowing list" << endl
      << "5. borrow" << endl
      << "6. borrow back";

  int choice = getInput<int>("enter code: ");
  switch (choice)
  {
  case 1:
  {
    string
        uname = getInput<string>("username: "),
        pass = getInput<string>("password: ");

    try
    {
      login(uname, pass);
    }
    catch (char *err)
    {
    }

    break;
  }

  case 2:
  {
    cout
        << "1. show" << endl
        << "2. set sort" << endl
        << "3. set search" << endl
        << "4. discard session" << endl;

    int choice = getInput<int>("enter code: ");
    switch (choice)
    {
    case 1:
    {
    }

    case 3:
    {
      int bid = getInput<int>("enter book id: ");
      // TODO enter personal info
      break;
    }

    default:
    {
      // err
      break;
    }
    }
  }

  case 3:
  {
    int bid = getInput<int>("enter book id: ");
    // TODO enter personal info
    break;
  }

  default:
  {

    // err
    break;
  }
  }
}