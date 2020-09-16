#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<lld>::max();

/*
g++ -std=c++11 a-alien.cpp -o k
*/
int main() {
    freopen("acm.in", "r", stdin);
    freopen("acm.out", "w", stdout);

    int n, m, i, j;
    cin >> n >> m;
    int a[n]; int b[m];
    for(i = 0; i < n; i++)
        cin >> a[i];
    for(i = 0; i < m; i++)
        cin >> b[i];

    //cout << "DEBUG" << endl;
    string o = "";
    for(i = 0; i < n; i++) {
        o += "(10 ";
        for(j = 0; j < a[i]; j++) {
            o += " - 1";
            if(j == a[i] - 1) o += ")";
            else o += " ";
        }
        if(i == n - 1) o += " = 0";
        else o += " * ";
    }
    cout << o << endl;

    return 0;
}
