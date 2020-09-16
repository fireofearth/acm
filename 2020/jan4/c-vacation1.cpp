#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;

/*
g++ -std=c++11 c-vacation.cpp -o k
version submitted and accepted
*/
int main() {
    int N, a, b ,c;
    cin >> N;
    vector<vector<int>> v; // a[0] a ; a[1] b ; a[2] c
    v.push_back(vector<int>());
    v.push_back(vector<int>());
    v.push_back(vector<int>());
    for(int i = 0; i < N; i++) {
        cin >> a >> b >> c;
        v[0].push_back(a);
        v[1].push_back(b);
        v[2].push_back(c);
    }

    vector<vector<int>> h;
    h.push_back(vector<int>(N));
    h.push_back(vector<int>(N));
    h.push_back(vector<int>(N));
    h[0][0] = v[0][0];
    h[1][0] = v[1][0];
    h[2][0] = v[2][0];
    for(int i = 1; i < N; i++) {
        for(int j = 0; j < 3; j++) {
            int k1 = (j == 0 ? 1 : 0);
            int k2 = ((j == 0 || j == 1) ? 2 : 1);
            h[j][i] = v[j][i] + max(h[k1][i-1], h[k2][i-1]);
        }
    }
    cout << max(h[0][N-1], max(h[1][N-1], h[2][N-1])) << endl;

    return 0;
}
