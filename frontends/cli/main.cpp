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
        << "1. " << dye::blue(isLoggedIn() ? "logout" : "login") << endl
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
      if (isLoggedIn())
      {
        logout();
        print_info("logged out");
      }

      else
      {
        string
            uname = getInput<string>("username: "),
            pass = getInput<string>("password: ");

        try
        {
          login(uname, pass);
          print_success("logged in successfully");
        }
        catch (const char *err)
        {
          print_err(err);
        }
      }

      break;
    }

    case 2:
    {
      // filters
      // searchText
      while (true)
      {

        cout
            << "1. show by id" << endl
            << "2. show" << endl
            << "3. set sort" << endl
            << "4. set search name" << endl
            << "5. set filter" << endl
            << "6. quit/discard session" << endl;

        int choice = getInput<int>("enter code: ");
        switch (choice)
        {
        case 1:
        {
          int bid = getInput<int>("enter book id: ");

          try
          {
            auto book = getBook(bid);
            print_info(full_info(*book));
          }
          catch (const char *err)
          {
            print_err(err);
          }

          break;
        }
        case 2:
        {
          break;
        }
        case 3:
        {
          int bid = getInput<int>("enter book id: ");
          // TODO enter personal info
          break;
        }

        default:
        {
          break;
        }
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