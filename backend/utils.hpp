#include <locale>
#include <string>

using namespace std;

string s2lower(string s) {        
    for(char &c : s)
        c = tolower(c);
    return s;
}