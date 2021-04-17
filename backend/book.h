#pragma once

#include <string>
#include <vector>

#include "date.h"
using namespace std;

struct Book
{
  string
      name,
      category,
      authorName;
  int
      id,
      releaseYear,
      version;
  Date
      comeInLib;

  // Book();
};

extern vector<Book *> bookList;

void addBook(Book *newBook);
void deleteBook(Book *book);
vector<Book *> sortBy(bool (*cmpFunc)(Book *b1, Book *b2), bool asc);
vector<Book *> filterBy(bool (*pred)(Book *b));