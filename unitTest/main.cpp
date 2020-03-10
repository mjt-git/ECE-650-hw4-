#include <iostream>
#include <fstream>
#include <pqxx/pqxx>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

void insertApos(string & str) {   // add ' to string if content contains '
  size_t pos = -1;
  size_t aposIdx;
  while((aposIdx = str.find("'", pos + 1)) != string::npos) {
    str.insert(aposIdx, "'");
    pos = aposIdx + 2;
  }
}

int main() {
  string str = "'";
  insertApos(str);
  cout << str << endl;
  return 0;
}
