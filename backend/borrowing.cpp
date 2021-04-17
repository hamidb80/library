// #include "book.h"
#include "user.h"
#include "borrowing.h"

using namespace std;

vector<Borrowing *> borrowingList;

void borrow(User *user, Book *book) {}
void giveBack(Book *book) {}
Borrowing *getBorrowed(Book *book)
{
  for (int i = 0; i < borrowingList.size(); i++)
    if (book->id == borrowingList[i]->book->id)
      return borrowingList[i];

  throw "this book is not borrowed for now";
}