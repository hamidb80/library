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

static string to_string(User u)
{
  return (
      "name:\t" + u.name + "\n" +
      "phone number:\t" + u.phoneNumber + "\n" +
      "national code:\t" + u.nationalCode + "\n" +
      "email:\t" + u.email);
}
static User json2user(JsonObject jo)
{
  return User(
      jo["name"],
      jo["phoneNumber"],
      jo["nationalCode"],
      jo["email"]);
}
static JsonObject user2json(User usr)
{
  JsonObject jo;

  jo["name"] = usr.name;
  jo["phoneNumber"] = usr.phoneNumber;
  jo["nationalCode"] = usr.nationalCode;
  jo["email"] = usr.email;

  return jo;
}