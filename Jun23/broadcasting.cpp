#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned long long int mylong;

int main(/*int argc, char* argv[]*/) {
  ofstream outf("output.txt");
  ifstream inf("input.txt");
  mylong n; // # of computers
  mylong k; // max # of computers can send
  mylong pcs;
  mylong time;
  
  while (!inf.eof()) {
    inf >> n;
    if( inf.eof() ) break;
    inf >> k;
    time = 0;
    pcs = 1;
    while(pcs < n) {
      pcs += pcs * k;
      time++;
    }
    outf << time << "\n";
  }
 
  return 0;
}

/*
g++ -std=c++11 -o broadcasting broadcasting.cpp

n = 25; k = 5

1 = 1
1 + 5 = 6
1 + 5 + 30 = 36
1 + 5 + 30 + 180 = 216

n = 
*/
