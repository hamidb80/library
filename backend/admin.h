#pragma once

#include <string>
#include <vector>
#include <functional>
#include <ArduinoJson.h>

using namespace std;

struct Admin
{
  int id;
  string name;
  string hashedPass;
  Admin(string _n, string _hp) : name(_n), hashedPass(_hp) {}
};

extern vector<Admin *> adminList;
extern int adminNextId;
extern Admin *noOne, *currentAdmin;

void login(string userName, string pass);
bool isLoggedIn();
void logout();
void registerAdmin(string name, string pass);
void removeAdmin(Admin *a);

void saveAdminsToJson(string path);
Admin *json2admin(JsonObject jo);
JsonObject to_json(Admin *admn);