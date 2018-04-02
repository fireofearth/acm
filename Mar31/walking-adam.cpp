#include <iostream>
#include <vector>
using namespace std;


int main() {
  int T = 0; // # of test cases
  int standing = 0; // accumulator of # times consecutive walks
  // int longest = 0; // greatest # times consecutive walks
  string hands;
  vector<int> longest_steps;

  // cout << "DEBUG " << hands.max_size() << endl;

  cin >> T;
  for(int i = 0; i < T; i++) { // test cases
    cin >> hands;

    standing = 0;
    // longest = 0;
    /*for(int walk = 0; walk < hands.size(); walk++) {
      if(standing > longest) longest = standing;
      if(hands[walk] == 'D') {
        standing = 0; // reset
      } else standing++;
    }
    if(standing > longest) longest = standing;*/

    for(int walk = 0; walk < hands.size(); walk++) {
      if(hands[walk] == 'U')
        standing++;
      else break;
    }
    longest_steps.push_back(standing);

    // longest_steps.push_back(longest);
  }

  for(int& a : longest_steps)
    cout << a << endl;

  return 0;
}