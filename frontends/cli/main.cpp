#include <iostream>
#include <vector>

// https://github.com/nlohmann/json

#include "../../backend/date.h"
#include "../../backend/admin.h"
#include "../../backend/user.h"
#include "../../backend/book.h"
#include "../../backend/borrowing.h"
#include "../../backend/sort.h"

#include "printer.h"
#include "color.hpp"

using namespace std;

string stringer(string s)
{
  return s == "" ? "not set" : s;
}

int main()
{
  add10Books();

  cout
      << dye::yellow_on_grey("~~~~~~~~~ library [CLI] ~~~~~~~~~") << endl
      << endl;

  while (true)
  {

    cout << "1. " << dye::bright_white_on_blue(isLoggedIn() ? "logout" : "login") << endl;

    if (isLoggedIn())
      cout
          << "2. " << dye::black_on_blue("add book") << endl
          << "3. " << dye::black_on_light_purple("delete book(s)") << endl;
    cout
        << "4. " << dye::black_on_light_red("books list") << endl
        << "5. " << dye::black_on_green("check book status") << endl
        << "6. " << dye::black_on_yellow("borrowing list") << endl;

    if (isLoggedIn())
      cout
          << "7. " << dye::bright_white_on_purple("borrow") << endl
          << "8. " << dye::green_on_grey("give back") << endl
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
      if (isLoggedIn())
      {
        try
        {
          Book *newb = new Book(
              getLine("name: "),
              getLine("category: "),
              getLine("author name: "),
              getInput<int>("release year: "),
              getInput<int>("version: "),
              Date(getInput<string>("come In Lib date: ")));

          addBook(newb);
          print_success(
              "book successfully added to lib with id:" +
              to_string(newb->id));
        }
        catch (const char *err)
        {
          print_err(err);
        }
      }
      break;
    }

    case 3:
    {
      if (isLoggedIn())
      {
        int bid = getInput<int>("enter book id: ");

        try
        {
          auto book = getBook(bid);
          deleteBook(book);
        }
        catch (const char *err)
        {
          print_err(err);
        }
      }
      break;
    }

    case 4:
    {
      auto shouldContinue = true;
      Sort sort("", true);
      BookFilter filtering;

      while (shouldContinue)
      {

        cout
            << indent(2) << "1. show by id" << endl
            << indent(2) << "2. show list" << endl
            << indent(2) << "3. set sort" << endl
            << indent(2) << "4. set filter" << endl
            << indent(2) << "5. quit/discard session" << endl;

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
          cout
              << endl
              << "search for books with:" << hue::aqua << endl
              << "--"
              << "name:\t" << stringer(filtering.name) << endl
              << "--"
              << "category:\t" << stringer(filtering.category) << endl
              << "--"
              << "author Name:\t" << stringer(filtering.authorName) << endl
              << "--"
              << "year:\t" << stringer(to_string(filtering.releaseYear) == "0" ? "" : to_string(filtering.releaseYear)) << endl
              << hue::reset
              << "sort by:" << hue::aqua << endl
              << stringer(sort.by) << ", " << (sort.asc ? "asc" : "desc")
              << hue::reset;

          auto bkl = filterBy(bookList, filtering);

          if (sort.by != "")
            bkl = sortBy(bkl, sort.by, sort.asc);

          if (bkl.size() == 0)
            print_err("no book found");

          else
            for (int i = 0; i < bkl.size(); i++)
              printMessage("#" + to_string(bkl[i]->id), short_info(*bkl[i]));

          cout << endl;
          break;
        }
        case 3:
        {
          cout << dye::black_on_aqua("::: sort :::") << endl;

          for (int i = 0; i < bookCharacteristicsLen; i++)
            cout << indent(4)
                 << i + 1 << ". " << bookCharacteristics[i] << endl;

          int choice = getInput<int>() - 1;
          if (choice < bookCharacteristicsLen && choice >= 0)
            sort.by = bookCharacteristics[choice];

          else
            print_err("the entred number is out of range");

          break;
        }
        case 4:
        {
          cout
              << dye::black_on_green("::: filter :::") << endl;

          cout
              << indent(4) << "1. name" << endl
              << indent(4) << "2. category" << endl
              << indent(4) << "3. author name" << endl
              << indent(4) << "4. release year" << endl;

          int choice = getInput<int>("select: ");
          switch (choice)
          {
          case 1:
          {
            filtering.name = getLine("name: ");
            break;
          }
          case 2:
          {
            filtering.category = getLine("category: ");
            break;
          }
          case 3:
          {
            filtering.authorName = getLine("author Name: ");
            break;
          }
          case 4:
          {
            filtering.releaseYear = getInput<int>("release Year: ");
            break;
          }

          default:
            break;
          }
          break;
        }
        case 5:
        {
          shouldContinue = false;
          break;
        }

        default:
        {
          break;
        }
        }
      }
      break;
    }

    case 5:
    {
      int bid = getInput<int>("enter book id: ");
      try
      {
        Book *b = getBook(bid); // chekc ofr exstance of the book
        try
        {
          auto brw = getBorrowed(b);
          printMessage(
              "Report",
              "is borrowd by: " + brw->user->name);
        }
        catch (...)
        {
          printMessage("Report", "is free");
        }
      }
      catch (const char *err)
      {
        print_err(err);
      }

      break;
    }

    case 6:
    {
      break;
    }
    case 7:
    {
      if(isLoggedIn())

      break;
    }
    case 8:
    {
      if(isLoggedIn())

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