#include <ArduinoJson.h>
#include <iostream>

#include "../utils/json.hpp"
using namespace std;

int main()
{
  auto doc = parseJson(readFile("database/books.json"));

  int nextId = doc["nextId"];
  cout << nextId;
  // cout << doc;
}