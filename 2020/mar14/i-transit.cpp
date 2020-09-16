#include <bits/stdc++.h>
using namespace std;

/*
g++ -std=c++11 i-transit.cpp -o k
*/
int main() {
    int s, t, n, i, j;
    cin >> s >> t >> n;
    int d[n+1];
    int b[n+1];
    int c[n+1];

    for(i = 0; i <= n; i++) {
        cin >> d[i];
    }
    for(i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(i = 1; i <= n; i++) {
        cin >> c[i];
    }
    int tt = s;
    tt += d[0];
    for(i = 1; i <= n; i++) {
        j = (tt % c[i]);
        if(j != 0)
            tt += c[i] - j;
        tt += b[i];
        tt += d[i];
    }

    if(tt <= t) cout << "yes" << endl;
    else cout << "no" << endl;

    return 0;
}
