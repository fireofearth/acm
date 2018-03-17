#include <iostream>
#include <cmath>
// #include <string>
// #include <vector>
using namespace std;

/*
You have a single 3D printer, and would like to use it to produce n

statues. However, printing the statues one by one on the 3D printer takes a long time, so it may be more time-efficient to first use the 3D printer to print a new printer. That new printer may then in turn be used to print statues or even more printers. Print jobs take a full day, and every day you can choose for each printer in your possession to have it print a statue, or to have it 3D print a new printer (which becomes available for use the next day).

What is the minimum possible number of days needed to print at least n
statues?


The input contains a single integer n (1 ≤ n ≤ 10000), the number of statues you need to print.
Output a single integer, the minimum number of days needed to print at least n statues.

g++ -std=c++11 -o 3d-printed 3d-printed.cpp

SUCCESS

Sample

input:  1
output: 1

input: 5
output: 4
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {

  int n = 0;
  
  cin >> n;

  if(n == 0) { cout << 0 << endl; return 0; }
  if(n < 0) { return 0; }

  cout << ( (int) ( ceil( log2((double) n) ) + 1 ) ) << endl;

  return 0;
}