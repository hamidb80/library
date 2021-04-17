#pragma once

#include "date.h"
#include "book.h"
#include "user.h"

using namespace std;

struct Borrowing
{
  User *user;
  Book *book;

  Date
      recvDate,
      giveBackDate;
};

extern vector<Borrowing*> borrowingList;

void borrow(User *user, Book *book);
void giveBack(Book *book);
Borrowing* getBorrowed(Book *book);