#include <ctime>
#include <ArduinoJson.h>
#include "user.h"
#include "date.h"
#include "borrowing.h"

using namespace std;

vector<Borrowing *> borrowingList;
int bookNextId = 0;

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

  brw->id = bookNextId++;
  borrowingList.push_back(brw);
}
void giveBack(Book *book)
{
  for (int i = 0; i < borrowingList.size(); i++)
  {
    auto brw = borrowingList[i];
    if (book->id == brw->book->id)
    {
      brw->giveBackDate = getNow();
      return;
    }
  }
}
Borrowing *getBorrowingInfo(Book *book)
{
  for (int i = 0; i < borrowingList.size(); i++)
  {
    auto brw = borrowingList[i];
    if (book->id == brw->book->id)
      return brw;
  }

  throw "this book is not borrowed for now";
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
JsonObject to_json(Borrowing *brw)
{
  JsonObject jo;

  jo["id"] = brw->id;
  jo["bookId"] = brw->book->id;
  jo["user"] = to_json(brw->user);
  jo["recvDate"] = to_string(brw->recvDate);
  jo["giveBackDate"] = to_string(brw->giveBackDate);

  return jo;
}