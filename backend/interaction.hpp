#pragma once

#include <string>
#include <vector>

#include "../utils/json.h"
#include "../utils/database.h"

#include "book.h"
#include "borrowing.h"
#include "admin.h"

using namespace std;
using namespace admin;
using namespace borrowing;
using namespace book;

// saving ---------------------------------------
void saveBooksAsFile(string path)
{
  auto db = initDB<Book>(bookList, book2json, book::nextId);
  saveDB(path, db);
}

void saveBorrowingsAsFile(string path)
{
  auto db = initDB<Borrowing>(borrowingList, borrowing2json, borrowing::nextId);
  saveDB(path, db);
}

void saveAdminsAsFile(string path)
{
  auto db = initDB<Admin>(adminList, admin2json, admin::nextId);
  saveDB(path, db);
}

// importing ---------------------------------------
void importBooksFromJson(string path)
{
  auto db = readJsonDB(path);
  parseDb(db, book::bookList, book::nextId, json2Book);
}

void importBorrowingsFromJson(string path)
{
  auto db = readJsonDB(path);
  parseDb(db, borrowing::borrowingList, borrowing::nextId, json2borrowing);
}

void importAdminsFromJson(string path)
{
  auto db = readJsonDB(path);
  parseDb(db, admin::adminList, admin::nextId, json2admin);
}