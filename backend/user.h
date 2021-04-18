#pragma once

#include <string>
#include <ArduinoJson.h>

using namespace std;

struct User
{
  string
      name,
      phoneNumber,
      nationalCode,
      email;

  User(
      string _n,
      string _fn,
      string _nc,
      string _e) : name(_n),
                   phoneNumber(_fn),
                   nationalCode(_nc),
                   email(_e) {}
};

string to_string(User u);
User json2user(JsonObject jo);
JsonObject to_json(User usr);