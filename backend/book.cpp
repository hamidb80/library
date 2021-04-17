#include <string>
#include <vector>

#include "date.h"
#include "book.h"
using namespace std;

vector<Book *> bookList = {
    new Book(),
    new Book(),
    new Book(),
    new Book(),
    new Book(),
    new Book(),
    new Book(),
    new Book(),
    new Book(),
    new Book()};

void addBook(Book *newBook)
{
  bookList.push_back(newBook);
}
void deleteBook(Book *book)
{
  for (int i = 0; i < bookList.size(); i++)
    if (bookList[i]->id == book->id)
    {
      bookList.erase(bookList.begin() + i);
      delete book;
      return;
    }
}
vector<Book *> sortBy(bool (*cmpFunc)(Book *b1, Book *b2), bool asc)
{
  auto result = bookList;

  for (int i = 0; i < bookList.size(); i++)
    for (int j = i + 1; j < bookList.size(); j++)
      if (cmpFunc(bookList[i], bookList[j]) && asc)
        swap(bookList[i], bookList[j]);

  return result;
}
vector<Book *> filterBy(bool (*pred)(Book *b))
{
  vector<Book *> result;

  for (int i = 0; i < bookList.size(); i++)
    if (pred(bookList[i]))
      result.push_back(bookList[i]);

  return result;
}