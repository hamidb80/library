#pragma once

#include <ArduinoJson.h>
#include "fileio.h"

using namespace std;

static DynamicJsonDocument parseJson(string jsonString)
{
  DynamicJsonDocument doc(jsonString.length() * 10);
  DeserializationError error = deserializeJson(doc, jsonString);

  if (error)
    throw "error while parsing json";

  return doc;
}

static DynamicJsonDocument parseJsonFile(string path)
{
  return parseJson(readFile(path));
}