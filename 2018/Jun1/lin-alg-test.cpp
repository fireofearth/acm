#include <bits/stdc++.h>

using namespace std;
#define int long long

int runMe();

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; // the # of cases
  cin >> T;
  vector<int> Z(T);
  for(int i = 0; i < T; i++) {
    Z[i] = runMe();
  }
  for(int i = 0; i < T; i++) {
    cout << Z[i] << '\n';
  }

  return 0;
}

int runMe() {
  int n; // # of M
  int acc = 0; // # of M can be multiplied
  cin >> n;
  if(n == 1) {
    int a; int b;
    cin >> a >> b;
    return 0;
  }
  vector<int> a(n); // row of i-th matrix
  vector<int> b(n); // col of i-th matrix
  for(int k = 0; k < n; k++) {
    cin >> a[k] >> b[k];
  }

  

  // for(int i = 0; i < n - 1; i++) {
  //   for(int j = i + 1; j < n; j++) {
  //     if(b[i] == a[j]) acc++;
  //   }
  // }

  // for(int i = 0; i < n - 1; i++) {
  //   for(int j = i + 1; j < n; j++) {
  //     if(b[j] == a[i]) acc++;
  //   }
  // }

  return acc;
}

/*
g++ -std=c++11 -o lin-alg-test lin-alg-test.cpp
2
5
2 3
2 3
4 2
3 5
9 4
2
1 9
9 1


expected: 5
*/