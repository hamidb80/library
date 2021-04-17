#include "date.h"
using namespace std;

string to_string(Date d){
  return (
    to_string(d.year) + "/" + 
    to_string(d.month) + "/"+ 
    to_string(d.day));
}