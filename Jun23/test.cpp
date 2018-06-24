#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  string s ="asdf";
  vector<char> c;
  for(char ch : s) {
      c.push_back(ch);
  }

  for(char ch : c) {
      cout << ch << endl;
  }
  
  return 0;
}

/*
g++ -std=c++11 -o test test.cpp
*/