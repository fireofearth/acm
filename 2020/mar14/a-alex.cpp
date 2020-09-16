#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
g++ -std=c++11 a-alex.cpp -o k
*/
int main() {
    int k, m, n, i, j;
    bool w;
    bool a[k + 1];
    cin >> k >> m >> n;
    for(i = 0; i < m; i++)
        a[i] = false;
    for(i = m; i <= k; i++) {
        a[i] = false;
        if(i >= m) {
            for(j = max(0, i - n); j <= i - m; j++)
                a[i] = !a[j] || a[i];
        }
    }
    if(a[k]) {
        cout << "Alex" << endl;
    } else {
        cout << "Barb" << endl;
    }

    return 0;
}
