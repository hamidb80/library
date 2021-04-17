#pragma once

#include <string>
#include <vector>
#include <functional>

using namespace std;

struct Admin
{
  string name;
  string hashedPass;
  Admin(string _n, string _hp) : name(_n), hashedPass(_hp) {}
};

extern vector<Admin *> adminList;
extern Admin *noOne, *currentAdmin;

void login(string userName, string pass);
bool isLoggedIn();
void logout();
void registerAdmin(string name, string pass);
void removeAdmin(Admin *a);