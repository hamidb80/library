#pragma once

#include <ArduinoJson.h>

#include "date.h"
#include "book.h"
#include "user.h"

using namespace std;

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

extern vector<Borrowing *> borrowingList;

void addBorrow(int id, User user, Book *book, Date recvd, Date giveBack = Date());
void borrow(User user, Book *book);
void giveBack(Book *book);
Borrowing *getBorrowingInfo(Book *book);

JsonObject to_json(Borrowing *brw);
Borrowing *json2borrowing(JsonObject jo);