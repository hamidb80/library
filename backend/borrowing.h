#pragma once

#include <ctime>
#include <ArduinoJson.h>
#include "user.h"
#include "date.h"

using namespace std;
using namespace book;

struct Borrowing
{
  int id;
  User user;
  Book *book;

  Date
      recvDate,
      giveBackDate;

  Borrowing(
      Book *bk,
      User usr,
      Date rcv,
      Date gvBkDt) : user(usr),
                     book(bk),
                     recvDate(rcv),
                     giveBackDate(gvBkDt) {}
  Borrowing(Book *bk, User usr, Date rcv) : user(usr),
                                            book(bk),
                                            recvDate(rcv) {}

  bool is_free()
  {
    return !giveBackDate.isNone();
  }
};

using namespace std;

namespace borrowing
{
  vector<Borrowing *> borrowingList;
  int nextId = 0;

  void addBorrow(int id, User user, Book *book, Date recvd, Date giveBack)
  {
    auto brw = new Borrowing(book, user, recvd, giveBack);
    brw->id = id;
    borrowingList.push_back(brw);
  }
  void borrow(User user, Book *book)
  {
    auto dnow = getNow();
    auto brw = new Borrowing(book, user, dnow);

    brw->id = nextId++;
    borrowingList.push_back(brw);
  }
  void giveBack(Book *book)
  {
    for (int i = 0; i < borrowingList.size(); i++)
    {
      auto brw = borrowingList[i];
      if (book->id == brw->book->id)
      {
        if (brw->giveBackDate.isNone())
        {
          brw->giveBackDate = getNow();
          return;
        }
        break;
      }
    }
    throw "this book is not borrowed";
  }
  Borrowing *getActiveBorrowingInfo(Book *book)
  {
    for (int i = 0; i < borrowingList.size(); i++)
    {
      auto brw = borrowingList[i];
      if (book->id == brw->book->id && !brw->is_free())
        return brw;
    }

    throw "this book is not borrowed for now";
  }
  string to_string(Borrowing *brw)
  {
    return "---book:\n" + short_info(*brw->book) +
           "\n---is borrowed by:\n" + to_string(brw->user) +
           "\ngiven in: " + to_string(brw->recvDate) +
           (brw->giveBackDate.isNone() ? "\nnot returned yet"
                                       : "\nreturned in: " + to_string(brw->recvDate));
  }

  Borrowing *json2borrowing(JsonObject jo)
  {
    auto Borrowingref = new Borrowing(
        getBook(jo["bookId"].as<int>()),
        json2user(jo["user"].as<JsonObject>()),
        Date(jo["recvDate"].as<string>()),
        Date(jo["giveBackDate"].as<string>()));

    Borrowingref->id = jo["id"].as<int>();
    return Borrowingref;
  }
  JsonObject borrowing2json(Borrowing *brw)
  {
    JsonObject jo;

    jo["id"] = brw->id;
    jo["bookId"] = brw->book->id;
    jo["user"] = user2json(brw->user);
    jo["recvDate"] = to_string(brw->recvDate);
    jo["giveBackDate"] = to_string(brw->giveBackDate);

    return jo;
  }
} // namespace borrowing
