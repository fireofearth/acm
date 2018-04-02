#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int main() {
  unsigned int T; // # of test cases
  unsigned int Q;
  unsigned int N;
  float b;
  vector<unsigned int> vec;

  // query
  int qType; // should be 1,2, or 3
  int L;
  int R;
  unsigned int x;
  unsigned int sum;

  // output
  vector<unsigned int> output;

  cin >> T;
  for(int i = 0; i < T; i++) { // test cases

    cin >> N >> Q;
    
    vec.clear();
    vec.reserve(N);

    for(int j = 0; j < N; j++)
      cin >> vec[j];

    // 
    for(int k = 0; k < Q; k++) {
      cin >> qType;
      cin >> L >> R;
      if(qType == 3)
        cin >> x;
      // cout << qType << L << R << x;
      L--; // R--; // convert to 0-base

      if(qType == 1) { // query 1
        // cout << "DEBUG: qType=1" << endl;
        for(int j = L; j < R; j++) {
          vec[j] = (unsigned int) floor( sqrt( vec[j] ) );
          // cout << "DEBUG: qType=1 vec_j=" << vec[j] << endl;
        }
      } else if(qType == 2) { // query 2
        // cout << "DEBUG: qType=2" << endl;
        sum = 0;
        for(int j = L; j < R; j++) {
          sum += vec[j];
        }
        // cout << "DEBUG: qType=2 sum=" << sum << endl;
        output.push_back(sum);
      } else { // query 3
        // cout << "DEBUG: qType=3" << endl;
      // if(qType == 3) { // query 3
        for(int j = L; j < R; j++) {
          vec[j] += x;
        }
      }
    } // end k loop
  }

  for(unsigned int& a : output)
    cout << a << endl;

  return 0;
}