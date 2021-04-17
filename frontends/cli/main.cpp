#include <iostream>
#include <vector>

// https://github.com/nlohmann/json

#include "../../backend/date.h"
#include "../../backend/admin.h"
#include "../../backend/user.h"
#include "../../backend/book.h"
#include "../../backend/borrowing.h"

#include "utils.h"
#include "color.hpp"

using namespace std;

int main()
{
  cout
      << dye::yellow_on_grey("~~~~~~~~~ library [CLI] ~~~~~~~~~") << endl
      << endl;

  while (true)
  {
    cout
        << "1. " << dye::blue("login/logout") << endl
        << "2. " << dye::red("show/search books") << endl
        << "3. " << dye::purple("book status") << endl
        << "4. " << dye::aqua("borrowing list") << endl
        << "5. " << dye::yellow("borrow") << endl
        << "6. " << dye::green_on_grey("borrow back") << endl
        << endl;

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
}