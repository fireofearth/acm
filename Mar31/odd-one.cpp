#include <iostream>
#include <vector>
using namespace std;

/* find oddness of the majority
0 => even
1 => odd
*/
int findOddness(int c1, int c2, int c3) {
  if(c1 % 2 == c2 % 2) return c1 % 2;
  else if(c2 % 2 == c3 % 2) return c2 % 2;
  else return c3 % 2;
}

/*
1 0 1
1 0 0
0 1 1
0 1 0
*/

int main() {
  int T = 0; int N; int C; int parity;
  vector<int> input;
  vector<int> output; // base-1 index of # diff
  
  cin >> T;
  for(int i = 0; i < T; i++) { // test cases
    cin >> N;
    input.clear();

    for(int j = 0; j < N; j++) { // per case
      cin >> C;
      input.push_back(C);
    }

    parity = findOddness(input[0], input[1], input[2]);
    for(int k = 0; k < input.size(); k++) {
      if(input[k] % 2 != parity) {
        output.push_back(k + 1);
        break;
      }
    }
  }

  for(int& a : output)
    cout << a << endl;

  return 0;
}