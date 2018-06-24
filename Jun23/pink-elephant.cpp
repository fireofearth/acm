#include <iostream>
#include <fstream>

using namespace std;

unsigned nChoosek(unsigned long long int n, unsigned long long int k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    unsigned long long int result = n;
    for( unsigned long long int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

int main(/*int argc, char* argv[]*/) {
  ofstream outf("output.txt");
  ifstream inf("input.txt");
  unsigned long long int n; unsigned long long int m;
  
  while (!inf.eof()) {
      inf >> n;
      if( inf.eof() ) break;
      inf >> m;
      unsigned long long int out = nChoosek(m,n);
      //cout << n << " "<< m << " " << out << "\n";

      outf << out % (unsigned long long int) 1000000007 << "\n";
  }
 
  return 0;
}

/*
g++ -std=c++11 -o pink-elephant pink-elephant.cpp

*/
