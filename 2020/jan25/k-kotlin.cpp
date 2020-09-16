#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<int>::max();

/*
g++ -std=c++11 k-kotlin.cpp -o k
*/
inline int f(int &k, int &l, int h, int w, int n) {
    for(k = 1; k <= (int) ceil((float) h / 2.0); k += 1) {
        for(l = 1; l <= (int) ceil((float) w / 2.0); l += 1) {
            if(n == k * l) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    freopen("kotlin.in", "r", stdin);
    freopen("kotlin.out", "w", stdout);

    int h, w, n;
    int k = 1;
    int l = 1;
    cin >> h >> w >> n;
    if(!f(k, l, h, w, n)) {
        cout << "Impossible" << endl;
        return 0;
    }
    //cout << n << " " << k << " " << l << endl;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(i % 2 == 1 || j % 2 == 1) {
                cout << "#";
            } else if(i > 2*k - 1 || j > 2*l - 1) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }

    return 0;
}

