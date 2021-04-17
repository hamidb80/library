#include <string>
#include <vector>

#include "date.h"
#include "book.h"

#define endl "\n"

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
Book *getBook(int book_id)
{
  for (int i = 0; i < bookList.size(); i++)
    if (bookList[i]->id == book_id)
      return bookList[i];

  throw "there is no book with this id";
}
string full_info(Book book)
{
  return (
      "id:\t" + to_string(book.id) + endl +
      "name:\t" + book.name + endl +
      "category:\t" + book.category + endl +
      "author Name:\t" + book.authorName + endl +
      "version:\t" + to_string(book.version) + endl +
      "release Year:\t" + to_string(book.releaseYear) + endl +
      "come In Lib:\t" + to_string(book.comeInLib) + endl);
}
string shortInfo(Book book)
{
  return (
      "id:\t" + to_string(book.id) + endl +
      "name:\t" + book.name + endl +
      "category:\t" + book.category + endl);
}
vector<Book *> sortBy(vector<Book *> bkl, bool (*cmpFunc)(Book *b1, Book *b2), bool asc)
{
  auto result = bkl;

  for (int i = 0; i < result.size(); i++)
    for (int j = i + 1; j < result.size(); j++)
      if (cmpFunc(result[i], result[j]) && asc)
        swap(result[i], result[j]);

  return result;
}
vector<Book *> filterBy(vector<Book *> bkl, bool (*pred)(Book *b))
{
  vector<Book *> result;

  for (int i = 0; i < bkl.size(); i++)
    if (pred(bkl[i]))
      result.push_back(bkl[i]);

  return result;
}