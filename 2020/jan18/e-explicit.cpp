#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<lld>::max();

/*
g++ -std=c++11 e-explicit.cpp -o k
*/
int main() {
    freopen("explicit.in", "r", stdin);
    freopen("explicit.out", "w", stdout);

    int i, j, k;
    bool a[10];
    bool o = false;
    for(i = 0; i < 10; i++) {
        cin >> k;
        a[i] = (bool) k;
    }
    // pairs
    for(i = 0; i < 9; i++) {
        for(j = i + 1; j < 10; j++) {
            if(a[i] || a[j]) o = !o;
        }
    }

    // triplets
    for(i = 0; i < 8; i++) {
        for(j = i + 1; j < 9; j++) {
            for(k = j + 1; k < 10; k++) {
                if(a[i] || a[j] || a[k]) o = !o;
            }
        }
    }
    cout << o << endl;

    return 0;
}
