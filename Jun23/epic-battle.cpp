#include <iostream>
#include <fstream>

using namespace std;

int main(/*int argc, char* argv[]*/) {
  ofstream outf("output.txt");
  ifstream inf("input.txt");
  unsigned int n; unsigned int m; int acc;
  
  while (true) {
    acc = 0;
    inf >> n;
    if( inf.eof() ) break;
    int a[n];
    for(int i = 0; i < n; i++) {
      inf >> a[i];
    }
    for(int i = 0; i < n; i++) {
      acc += (a[i] - 1);
    }
    
    outf << (acc % 2 == 1 ? "Constantine" : "Mike") << "\n";
  }
 
  return 0;
}

/*
g++ -std=c++11 -o epic-battle epic-battle.cpp

n piles; a_i stones
1 <= n <= 20
1 <= a_i <= 40
constance -> starts
mike

if odd constance loses
if event constance wins

2 2 C
2 1 1 M
1 1 1 1 C

2 1 1 C
1 1 1 1 M

*/
