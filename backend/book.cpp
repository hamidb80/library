#include <string>
#include <vector>
#include <algorithm>

#include "utils.hpp"
#include "date.h"
#include "book.h"

#include "../utils/json.hpp"

#define endl "\n"
using namespace std;

vector<Book *> bookList = {};

int nextId = 0;

void addBook(Book *b)
{
  b->id = nextId++;
  bookList.push_back(b);
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
string short_info(Book book)
{
  return (
      "id:\t" + to_string(book.id) + endl +
      "name:\t" + book.name + endl +
      "author Name:\t" + book.authorName + endl +
      "category:\t" + book.category);
}

bool compare(string by, Book *a, Book *b)
{
  bool res;
  if (by == "name")
    return s2lower(a->name) > s2lower(b->name);
  else if (by == "id")
    return a->id > b->id;
  else if (by == "category")
    return s2lower(a->category) > s2lower(b->category);
  else if (by == "authorName")
    return s2lower(a->category) > s2lower(b->category);
  else if (by == "version")
    return a->version > b->version;
  else if (by == "releaseYear")
    return a->releaseYear > b->releaseYear;
  else if (by == "comeInLib")
    return compare(a->comeInLib, b->comeInLib);

  throw "no such characteristic in Date object";
}

vector<Book *> sortBy(vector<Book *> bkl, string by, bool asc)
{
  for (int i = 0; i < bkl.size(); i++)
    for (int j = i + 1; j < bkl.size(); j++)
      if (compare(by, bkl[i], bkl[j]) == asc)
        swap(bkl[i], bkl[j]);

  return bkl;
}
vector<Book *> filterBy(vector<Book *> bkl, BookFilter bf)
{
  vector<Book *> result;

  for (int i = 0; i < bkl.size(); i++)
  {
    Book *b = bkl[i];
    bool shouldAppend = ((bf.name == "" || b->name.find(bf.name) != -1) &&
                         (bf.category == "" || b->category == bf.category) &&
                         (bf.authorName == "" || b->authorName == bf.authorName) &&
                         (bf.releaseYear == 0 || b->releaseYear == bf.releaseYear));

    if (shouldAppend)
      result.push_back(bkl[i]);
  }

  return result;
}

Book *json2Book(JsonObject jo)
{
  auto bookref = new Book(
      jo["name"],
      jo["category"],
      jo["authorName"],
      jo["releaseYear"],
      jo["version"],
      Date(jo["comeInLib"]));

  bookref->id = jo["id"];
  return bookref;
}
JsonObject to_json(Book *bk)
{
  JsonObject jo;

  jo["id"] = bk->id;
  jo["name"] = bk->name;
  jo["category"] = bk->category;
  jo["authorName"] = bk->authorName;
  jo["comeInLib"] = to_string(bk->comeInLib);
  jo["version"] = bk->version;
  jo["releaseYear"] = bk->releaseYear;

  return jo;
}