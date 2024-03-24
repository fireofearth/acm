#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

int max_is(vector<int> a) {
    int n = a.size();
    if(n == 0) return 0;
    vector<int> memo(n);
    memo[0] = 0;
    memo[1] = a[0];
    for(int i = 2; i <= n; i++) {
        memo[i] = max(memo[i-2]+a[i-1], memo[i-1]);
    }
    return memo[n];
}

/*
Maximum independent set on a line using DP
g++ -std=c++11 maxindset.cpp -o k

in:
8
4 5 4 1 1 8 3 5

out:
21

in:
10
1 2 4 1 8 1 16 32 64 1

out:
93

*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    cout << max_is(a) << endl;
    return 0;
}
