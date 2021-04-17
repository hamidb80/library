#include <string>
#include <vector>
#include <algorithm>

#include "utils.hpp"
#include "date.h"
#include "book.h"

#define endl "\n"

using namespace std;

vector<Book *> bookList = {};

int lastBookId = 0;

void add10Books()
{
  Book *bs[10] = {

      new Book(
          "C++",
          "programming",
          "Richard Man",
          1986,
          3,
          Date(1987, 1, 1)),
      new Book(
          "OOP is a mess",
          "programming",
          "Samir Rahmani",
          2019,
          1,
          Date(2019, 11, 3)),
      new Book(
          "Human nature",
          "biology",
          "Ahmad Irani",
          2003,
          4,
          Date(2007, 4, 27)),
      new Book(
          "the God",
          "Spiritual",
          "Alex Noah",
          2005,
          1,
          Date(2006, 1, 8)),
      new Book(
          "bad economous",
          "economous",
          "Mehoul Souri",
          2010,
          18,
          Date(2010, 5, 3)),
      new Book(
          "mystery of time management",
          "life style",
          "Brayan Tracy",
          2011,
          1,
          Date(2013, 12, 8)),
      new Book(
          "be your self",
          "life style",
          "Nik Alice",
          2004,
          4,
          Date(2006, 3, 11)),
      new Book(
          "math 2",
          "scientific",
          "Tomas Newton",
          2016,
          7,
          Date(2017, 2, 18)),
      new Book(
          "OMG filling this stupid book list is so boring",
          "life style",
          "Hamid Bluri",
          2021,
          1,
          Date(2021, 4, 17)),
      new Book(
          "this is the last book i have to fill",
          "life style",
          "Hamid Bluri",
          2021,
          1,
          Date(2021, 4, 17)),
  };

  for (int i = 0; i < 10; i++)
    addBook(bs[i]);
}

void addBook(Book *b)
{
  b->id = lastBookId++;
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