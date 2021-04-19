#pragma onces

#include <fstream>
#include <string>

using namespace std;
static string readFile(string path)
{
  string res, myLine;
  ifstream myFile_Handler;

  myFile_Handler.open(path);

  if (myFile_Handler.is_open())
  {
    while (getline(myFile_Handler, myLine))
      res += myLine + "\n";

    myFile_Handler.close();
  }
  else
    throw "Unable to open the file!";

  return res;
}

static void saveFile(string path, string content)
{
  ofstream ofile;
  ofile.open(path);

  ofile << content;
  ofile.close();
}