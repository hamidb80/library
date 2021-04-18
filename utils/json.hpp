#include <ArduinoJson.h>
#include "fileio.hpp"

using namespace std;

DynamicJsonDocument parseJson(string jsonString)
{
  DynamicJsonDocument doc(jsonString.length() * 5);
  DeserializationError error = deserializeJson(doc, jsonString);

  if (error)
    throw "error while parsing json";

  return doc;
}

DynamicJsonDocument parseJsonFile(string path)
{
  return parseJson(readFile(path));
}