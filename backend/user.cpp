#include <string>
#include <ArduinoJson.h>

#include "user.h"

using namespace std;

string to_string(User u)
{
  return (
      "name:\t" + u.name + "\n" +
      "phone number:\t" + u.phoneNumber + "\n" +
      "national code:\t" + u.nationalCode + "\n" +
      "email:\t" + u.email);
}
User json2user(JsonObject jo)
{
  return User(
      jo["name"],
      jo["phoneNumber"],
      jo["nationalCode"],
      jo["email"]);
}
JsonObject to_json(User usr)
{
  JsonObject jo;

  jo["name"] = usr.name;
  jo["phoneNumber"] = usr.phoneNumber;
  jo["nationalCode"] = usr.nationalCode;
  jo["email"] = usr.email;

  return jo;
}