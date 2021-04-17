#include "date.h"
#include "book.h"
#include "user.h"
#include "borrowing.h"

using namespace std;

vector<Borrowing> borrowingList;

void borrow(User *user, Book *book) {}
void giveBack(Book *book) {}
bool isFree(Book *book)
{
  for (int i = 0; i < borrowingList.size(); i++)
    if (book->id == borrowingList[i].book->id)
      return false;

  return true;
}