#include <iostream>
#include <vector>

#include "../../backend/date.h"
#include "../../backend/admin.h"
#include "../../backend/user.h"
#include "../../backend/book.h"
#include "../../backend/borrowing.h"
#include "../../backend/sort.h"

#include "../../backend/interaction.hpp"

#include "../../utils/json.h"
#include "printer.h"
#include "color.hpp"

using namespace std;
using namespace book;
using namespace admin;
using namespace borrowing;

string stringer(string s)
{
  return s == "" ? "not set" : s;
}

void loadDataBase()
{
  importAdminsFromJson("./database/admins.json");
  importBooksFromJson("./database/books.json");
  importBorrowingsFromJson("./database/borrowings.json");
}

int main()
{
  cout
      << dye::yellow_on_grey("~~~~~~~~~ library [CLI] ~~~~~~~~~") << endl
      << endl;

  try
  {
    loadDataBase();
  }
  catch (const char *err)
  {
    print_err(err);
  }

  while (true)
  {
    if (isLoggedIn())
      cout
          << "0. " << dye::black_on_bright_white("import from json file") << endl;

    cout
        << "1. " << dye::bright_white_on_blue(isLoggedIn() ? "logout" : "login") << endl;

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
          << "9. " << dye::black_on_purple("save") << endl
          << endl;

    int choice = getInput<int>("enter code: ");
    switch (choice)
    {
    case 0:
    {
      cout
          << hue::aqua
          << "the path must have 3 files:" << endl
          << "  admins.json" << endl
          << "  books.json" << endl
          << "  borrowings.json" << endl
          << "default: ./database/" << endl
          << hue::reset;

      auto pathToFolder = getInput<string>("\npath to that folder: ");
      try
      {
        importBooksFromJson(pathToFolder + "books.json");
        importAdminsFromJson(pathToFolder + "admins.json");
        importBorrowingsFromJson(pathToFolder + "borrowings.json");
      }
      catch (const char *err)
      {
        print_err(err);
      }

      break;
    }
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
              printMessage("#" + to_string(i + 1), short_info(*bkl[i]));

          print_info(to_string(bkl.size()) + " result(s) found");
          break;
        }
        case 3:
        {
          cout << dye::black_on_aqua("::: sort :::") << endl;
          const int bookCharacteristicsLen = 7;
          const string bookCharacteristics[bookCharacteristicsLen] = {
              "name",
              "id",
              "category",
              "authorName",
              "version",
              "releaseYear",
              "comeInLib"};

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
          auto brw = getActiveBorrowingInfo(b);

          if (brw->is_free())
            throw "";

          printMessage("Report", to_string(brw));
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
      for (int i = 0; i < borrowingList.size(); i++)
      {
        auto brw = borrowingList[i];
        printMessage(
            "#" + to_string(brw->id), to_string(brw));
      }

      break;
    }
    case 7:
    {
      if (isLoggedIn())
      {
        int bid = getInput<int>("book id: ");
        User usr = User(
            getLine("your name: "),
            getInput<string>("phone number: "),
            getInput<string>("national code :"),
            getInput<string>("email: "));

        try
        {
          borrow(usr, getBook(bid));
        }
        catch (const char *err)
        {
          print_err(err);
        }
      }
      break;
    }
    case 8:
    {
      if (isLoggedIn())
      {
        int brid = getInput<int>("book id: ");
        try
        {
          giveBack(getBook(brid));
        }
        catch (const char *err)
        {
          print_err(err);
        }
      }
      break;
    }
    case 9:
    {
      if (isLoggedIn())
      {
        string pathToFolder = getLine("\npath to that folder: ");

        try
        {
          // FIXME: cannot save anything
          saveBooksAsFile(pathToFolder + "books.json");
          saveBorrowingsAsFile(pathToFolder + "borrowing.json");
          saveAdminsAsFile(pathToFolder + "admins.json");
        }
        catch (const char *err)
        {
          print_err(err);
        }
      }
      break;
    }
    default:
      break;
    }
  }
}
