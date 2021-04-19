#pragma once

#include <ArduinoJson.h>
#include <vector>
#include <string>

using namespace std;

struct DataBase
{
  int nextId;
  JsonArray dataList;
};

template <typename Type>
static DataBase initDB(vector<Type *> objectList, int nextId)
{
  JsonArray ja;

  for (auto obj : objectList)
    ja.add(to_json(obj));

  DataBase db;
  db.dataList = ja;
  db.nextId = nextId;
  return db;
}

template <class Type>
static void parseDb(DataBase db,
             vector<Type *> &dataList, int &nextId,
             Type *(*parseFunc)(JsonObject))
{
  for (auto obj : db.dataList)
    dataList.push_back(parseFunc(obj));

  nextId = db.nextId;
}

static DataBase readJsonDB(string path)
{
  auto doc = parseJsonFile(path);

  DataBase db;
  db.nextId = doc["nextId"];
  db.dataList = doc["list"];

  return db;
}

static void saveDB(string path, DataBase db)
{
  DynamicJsonDocument doc(db.dataList.memoryUsage() + 20);
  doc["list"] = db.dataList;
  doc["nextId"] = db.nextId;
}