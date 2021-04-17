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

    Book(
        string _name,
        string _category,
        string _authorName,
        int _releaseYear,
        int _version,
        Date _comeInLib) : name(_name),
                           category(_category),
                           authorName(_authorName),
                           releaseYear(_releaseYear),
                           version(_version),
                           comeInLib(_comeInLib)
    {
    }
};

struct BookFilter
{
    string
        name,
        category,
        authorName;
    int
        releaseYear;

    BookFilter() : name(""),
                   category(""),
                   authorName(),
                   releaseYear(0) {}
    // Date
    //     comeInLib;
};

extern vector<Book *> bookList;

const int bookCharacteristicsLen = 7;
const string bookCharacteristics[bookCharacteristicsLen] = {
    "name",
    "id",
    "category",
    "authorName",
    "version",
    "releaseYear",
    "comeInLib"};

void add10Books();
void addBook(Book *b);
void deleteBook(Book *book);
Book *getBook(int id);
string full_info(Book book);
string short_info(Book book);
vector<Book *> sortBy(vector<Book *> bkl, string by, bool asc);
vector<Book *> filterBy(vector<Book *> bkl, BookFilter bf);