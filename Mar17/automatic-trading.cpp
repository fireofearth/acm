/*

test cases:

input:
ABABABcABABAbAbab
3
0 2
1 6
0 7

SheSellsSeashellsByTheSeaShore
4
8 22
1 20
8 25
0 1

g++ -std=c++11 -o automatic-trading automatic-trading.cpp
*/

#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main() {

  string trade;
  int q;
  int k;

  cin >> trade;
  cin >> q;
  if(q < 1) return 0;

  pair<int,int> lookup[q];

  for(int i = 0; i < q; i++) {
    cin >> lookup[i].first;
    cin >> lookup[i].second;
  }

  for(int i = 0; i < q; i++) {

    k = 0;

    while(
      lookup[i].second + k < trade.size() && 
      trade[lookup[i].first + k] == trade[lookup[i].second + k]
      ) { k++; }

    cout << k << endl;
  }

  return 0;
}