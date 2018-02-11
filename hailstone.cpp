#include<iostream>
#include<string>

using namespace std;

struct testCase {
  int set;
  int n;
  int largest;
};

int main(int argc, char* argv[]) {
  int numCases;
  cin >> numCases;

  if(numCases < 1) return 0;
  testCase testCases[numCases - 1];

  for(int i = 0; i < numCases; i++) {
    cin >> testCases[i].set >> testCases[i].n;
  }

  for(int i = 0; i < numCases; i++) {
    int n = testCases[i].n;
    int largest = n;
    while(n > 1) {
      if(n % 2 == 0 /* even */)
        n = n / 2;
      else
        n = (3 * n) + 1;
      if(n > largest)
        largest = n;
      // cout << ++counter << " " << n 
      //   << " " << largest << endl;
    }
    testCases[i].largest = largest;
  }

  for(int i = 0; i < numCases; i++) {
    cout << testCases[i].set << " " 
      << testCases[i].largest << endl;
  }
}