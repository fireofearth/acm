#include<iostream>
#include<string>

using namespace std;

struct testCase {
  int num1;
  int num2;
};

int main(int argc, char* argv[]) {
  // int i; string s; double d;

  /*cout << argc << endl;
  cout << argv[0] << endl;
  cout << argv[1] << endl;*/

  int numCases;
  cin >> numCases;

  if(numCases < 1) return 0;

  testCase tc[numCases - 1];

  for(int i = 0; i < numCases; i++) {
    cin >> tc[i].num1 >> tc[i].num2;
  }

  for(int i = 0; i < numCases; i++) {
    cout << tc[i].num1 + tc[i].num2 << " ";
    cout << tc[i].num1 - tc[i].num2 << " ";
    cout << tc[i].num1 * tc[i].num2
      << endl;
  }
}