#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<int>::max();

/*
g++ -std=c++11 c-commuting.cpp -o k
did not work...

10
2 3 4 5 6 7 8 1 9 10

10
1 2 3 4 5 6 7 8 9 10

5
5 2 4 3 1
out: 1 2 2 2 5

8
8 3 2 4 6 5 7 1
out: 1 2 3 4 4 4 4 8

11
6 8 3 5 4 7 1 9 2 10 11
out: 1 2 3 3 3 6 7 8 9 3 3

9
2 1 4 3 5 7 8 9 6
*/
int main() {
    freopen("commuting.in", "r", stdin);
    freopen("commuting.out", "w", stdout);

    int n, i, j, k;
    cin >> n;
    int f[n+1];
    int g[n+1];
    for(i = 1; i < n+1; i++) {
        cin >> f[i];
        g[i] = 0;
    }

    // k is the first fixed point in f
    k = 0;
    for(i = 1; i < n+1; i++) {
        if((bool) g[i]) {
            // identified i as part of a cycle that has elements j < k
            // do nothing
        } else if(i == f[i]) {
            // i is a fixed point
            if(! (bool) k) {
                // landed on first fixed point
                k = i;
            }
            g[i] = k;
        } else {
            // i is in a cycle
            if(!k) {
                // has not reached first fixed point
                j = f[i];
                while(j != i) {
                    g[j] = j;
                    j = f[j];
                }
                g[i] = i;
            } else {
                // is past first fixed point
                g[i] = k;
            }
        }
    }

    //cout <<  "f(g) ";
    //for(i = 1; i < n+1; i++) {
    //    cout << f[g[i]];
    //    if(i == n) cout << endl;
    //    else cout << " ";
    //}
    //cout << "g(f) ";
    //for(i = 1; i < n+1; i++) {
    //    cout << g[f[i]];
    //    if(i == n) cout << endl;
    //    else cout << " ";
    //}

    for(i = 1; i < n+1; i++) {
        cout << g[i];
        if(i == n) cout << endl;
        else cout << " ";
    }

    return 0;
}
