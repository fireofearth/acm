#include <iostream>

using namespace std;

int main() {
  int T; // the # of cases
  cin >> T;
  int y[T]; // the # oranges before $ incr
  int x[T]; // % of $ incr
  for(int i = 0; i < T; i++) {
    cin >> y[i]; cin >> x[i];
  }

  for(int i = 0; i < T; i++) {
    // cout << ( (float) y[i] ) / ( 1.0 + (( (float) x[i]) * 0.01 ) ) << endl;
    cout << ( 100 * y[i] ) / ( 100 + x[i] ) << endl;
  }

  return 0;
}

/*
g++ -std=c++11 -o oranges oranges.cpp
3
10 25
300 20
550 100
*/