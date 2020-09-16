#include <bits/stdc++.h>
using namespace std;

static vector<int> v;

void fill_v(int n) {
    if(v.size() == 0) v.push_back(0);
    if(v.size() == 1) v.push_back(1);
    for(int i = v.size(); i <= n; i++) {
        v.push_back(v[v.size() - 1] + v[v.size() -2]);
        // cout << "> " << v.back() << endl;
    }
}

int fib(int n) {
    if(n < 0) throw invalid_argument("recv. neg. value");
    if(n >= v.size()) fill_v(n);
    return v[n];
}

/**
g++ -std=c++11 fib.cpp -o k
  */
int main() {
    int n;
    cin >> n;
    /*
    int n1, n2, n3;
    cin >> n1;
    cout << fib(n1) << endl;
    cin >> n2;
    cout << fib(n2) << endl;
    cin >> n3;
    cout << fib(n3) << endl;
    */
    return 0;
}
