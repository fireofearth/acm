#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
int V = 100000;
lld MAX = numeric_limits<lld>::max();

/*
g++ -std=c++11 e-knapsack.cpp -o k
*/
int main() {
    int N, W;
    cin >> N >> W;
    int w[N+1];
    int v[N+1];

    vector<vector<lld>> m; // items to choose from ; values
    m.push_back(vector<lld>());
    for(int i = 1; i < N+1; i++) {
        cin >> w[i] >> v[i];
        m.push_back(vector<lld>(V+1));
    }

    for(int j = 0; j < V+1; j++) {
        if(j == v[1])
            m[1][j] = w[1];
        else
            m[1][j] = MAX;
    }

    for(int i = 2; i < N+1; i++) {
        for(int j = 0; j < V+1; j++) {
            if(v[i] == j) {
                if(j - v[i] > -1 && m[i-1][j-v[i]] < MAX) {
                    m[i][j] = min((lld) w[i], min(m[i-1][j], m[i-1][j-v[i]] + (lld) w[i]));
                } else {
                    m[i][j] = min((lld) w[i], m[i-1][j]);
                }
            } else {
                if(j - v[i] > -1 && m[i-1][j-v[i]] < MAX) {
                    m[i][j]  = min(m[i-1][j], m[i-1][j-v[i]] + (lld) w[i]);
                } else {
                    m[i][j] = m[i-1][j];
                }
            }
        }
    }
    
    int o;
    for(int j = 1; j < V+1; j++) {
        if(m[N][j] <= W) {
            o = j;
        }
    }
    cout << o << endl;

    return 0;
}
