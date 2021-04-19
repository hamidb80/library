#pragma onces

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

void saveBooksAsFile(string path)
{
  // initDB<Book>(vector<Book*>(),3);
}

void saveBorrowingsAsFile(string path)
{
  // auto db = initDB<Borrowing>(borrowingList, bookNextId);
}

void saveAdminsAsFile(string path)
{
  // auto db = initDB<Admin>(adminList, adminNextId);
}