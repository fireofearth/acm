#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

/*
input:
3 3
1 2 20
2 3 10
1 3 100
4
1 3
3 1
1 2
2 3

expected:
20
-1
20
10

input:
6 6
1 2 20
2 3 10
4 5 10
5 6 10
1 3 100
6 4 10
8
1 3
3 1
1 2
2 3
1 4
4 1
4 6
4 5

expected:
20
-1
20
10
-1
-1
10
10

Floyd-Warshall
g++ -std=c++11 k-prestige.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; // nodes
    int m; // edges
    cin >> n >> m;

    int i, j, k;
    int u, v;
    int a, b;
    ll c;
    // Initialize Adj Mtx
    vector<vector<ll>> adj(
        n, vector<ll>(n, numeric_limits<ll>::max())
    ); // adj-mtx
    for(i = 0; i < n; i++) adj[i][i]  = 0;
    for(i = 0; i < m; i++) {
        cin >> u >> v >> c; // u => v has cost c
        u -= 1; v -= 1;
        adj[u][v] = c;
    }
    int q; // questions
    cin >> q;
    vector<pii> qs(q);
    for(i = 0; i < q; i++) {
        cin >> a >> b;
        a -= 1; b -= 1;
        qs[i] = {a, b};
    }

    // Floyd-Warshall
    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++) {
                adj[i][j] = min(adj[i][j], max(adj[i][k], adj[k][j]));
            }

    for(i = 0; i < q; i++) {
        c = adj[get<0>(qs[i])][get<1>(qs[i])];
        if(c == numeric_limits<ll>::max())
            cout << -1 << endl;
        else
            cout << c << endl;
    }

    return 0;
}

