#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;

/*
g++ -std=c++11 d-knapsack.cpp -o k
*/
int main() {
    int N, W;
    cin >> N >> W;
    int w[N+1];
    int v[N+1];
    vector<vector<lld>> m;
    m.push_back(vector<lld>(W+1));
    for(int i = 1; i < N+1; i++) {
        cin >> w[i] >> v[i];
        m.push_back(vector<lld>(W+1));
    }

    for(int j = 0; j < W+1; j++)
        m[0][j] = 0;

    for(int i = 1; i < N+1; i++) {
        for(int j = 0; j < W+1; j++) {
            if(w[i] > j) {
                m[i][j] = m[i-1][j];
            } else {
                m[i][j] = max(m[i-1][(j - w[i])] + (lld) v[i], m[i-1][j]);
            }
        }
    }

    cout << m[N][W] << endl;

    return 0;
}
