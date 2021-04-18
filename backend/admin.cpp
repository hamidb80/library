#include <string>
#include <vector>
#include <functional>
#include <ArduinoJson.h>
#include "../utils/json.hpp"

#include "admin.h"
using namespace std;

hash<string> hashFunc;
string getHash(string what)
{
  return to_string(hashFunc(what));
}
int nextId = 0;

vector<Admin *> adminList = {
    new Admin("admin", getHash("1234")),
};

Admin *noOne = new Admin("", ""),
      *currentAdmin = noOne;

void login(string userName, string pass)
{
  string hashedPass = getHash(pass);
  for (int i = 0; i < adminList.size(); i++)
  {

    if (adminList[i]->name == userName)
    {
      if (adminList[i]->hashedPass == hashedPass)
        currentAdmin = adminList[i];
      else
        throw "pass is not correct";
      return;
    }
  }

  throw "no such admin with this username";
}

bool isLoggedIn()
{
  return currentAdmin->name != "";
}
void logout()
{
  currentAdmin = noOne;
}
// void registerAdmin(string name, string pass)
// {
//   adminList.push_back(
//       new Admin(name, getHash(pass)));
// }
// void removeAdmin(Admin *a)
// {
//   for (int i = 0; i < adminList.size(); i++)
//     if (adminList[i]->name == a->name)
//     {
//       adminList.erase(adminList.begin() + i);
//       delete a;
//       return;
//     }
// }

Admin *json2admin(JsonObject jo)
{
  auto adminref = new Admin(
      jo["name"], jo["hashedPass"]);

  adminref->id = jo["id"];
  return adminref;
}
JsonObject to_json(Admin *admn)
{
  JsonObject jo;

  jo["id"] = admn->id;
  jo["name"] = admn->name;
  jo["hashedPass"] = admn->hashedPass;

  return jo;
}