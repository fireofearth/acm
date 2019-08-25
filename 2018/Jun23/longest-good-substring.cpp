#include <iostream>
#include <fstream>
#include <set>

using namespace std;

typedef unsigned int myint;

int main(/*int argc, char* argv[]*/) {
  ofstream outf("output.txt");
  ifstream inf("input.txt");
  
  myint k; // max # of chars
  string s;
  
  myint b;
  myint e;
  set<char> ch;
  myint lb;
  myint le;

  while (true) {
    inf >> k;
    if( inf.eof() ) break;
    inf >> s;

    b = 1;
    lb = 1;
    le = lb + k - 1;

    // abasdfjkl

    while(b + (le - lb + 1) < s.length()) {

      // prepare for the initial k length substring
      ch = set<char>();
      for(e = b; (e < b + k) && (e-1 <= s.length()) ; e++) {
        cout << s[e-1];
        ch.insert(s[e-1]);
      }
      
      // check the longest substring
      while((ch.find(s[e-1]) != ch.end() || ch.size() < k ) && e-1 <= s.length()) {
        cout << s[e-1];
        ch.insert(s[e-1]);
        if(e - b > le - lb) {
          lb = b;
          le = e;
        }
        e++;
      }
      cout << "\n";

      b++;
    }

    outf << lb << " " << le << "\n";
  }
 
  return 0;
}

/*
g++ -std=c++11 -o longest-good-substring longest-good-substring.cpp
*/