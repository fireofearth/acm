#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<lld>::max();
/*
g++ -std=c++11 a-alex.cpp -o k
*/
int main() {
    freopen("alex.in", "r", stdin);
    freopen("alex.out", "w", stdout);

    int h_in, w_in;
    float h, w;
    float a, b, t;

    while(cin >> h_in >> w_in) {
        h = (float) h_in;
        w = (float) w_in;
        if(h > w) {
            t = w;
            w = h;
            h = t;
        }
        
        // wide sheet
        if(h * 3.0 < w) {
            // conf horz
            cout << h << endl;
        } else {
            // do either
            a = w / 3.0;
            b = h / 2.0;
            if(a > b) {
                cout << a << endl;
            } else {
                cout << b << endl;
            }
        }
    }

    return 0;
}
