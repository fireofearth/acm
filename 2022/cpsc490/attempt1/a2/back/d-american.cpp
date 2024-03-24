#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

ll dijkstra(
    vector<vector<ll>> &cost,
    vector<vector<ll>> &adj,
    int j, int k, int mask
) {
    // dijkstra j => k
    priority_queue<
        pair<ll, int>, // cost, node
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > q;
    int u, v, i;
    ll d;
    q.emplace(0, j);
    while(!q.empty()) {
        tie(d, u) = q.top(); q.pop();
        if(u == k) return d;
        if(!((mask >> u) & 1)) continue;
        mask = mask ^ (1 << u);
        for(int v : adj[u]) {
            if(!((mask >> v) & 1)) continue;
            q.emplace(d + cost[u][v], v);

        }
    }
    throw runtime_error("dijkstra: cannot find path j => k");
}

/*
g++ -std=c++11 d-american.cpp -o k
18 < 32 == 2^5
2^18 = 262,144
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    int i, j, k, l;
    int u, v, s;
    int mask;
    ll d;
    cin >> n >> m;
    vector<vector<ll>> cost(n, vector<ll>(n, numeric_limits<ll>::max())); // adj-mtx
    vector<vector<ll>> adj(n); // adj-list
    for(i = 0; i < m; i++) {
        cin >> u >> v >> d;
        u -= 1; v -= 1;
        cost[u][v] = d;
        cost[v][u] = d;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> s;
    vector<ll> memo(1 << n);
    for(i = 0; i < n; i++) {
        j = (1 << i); // 1 = 2^0
        cost[j][j] = 0;
        j = (i << 18) + (1 << i); // f({i}, i) = 0;
        memo[j] = cost[s][i];
    }
    int key;
    for(i = 2; i < (1 << n); i++) {
        // iterate over subsets X where bitmasks equal i
        if((i >> s) & 1)
            // X contains s
            continue;
        for(j = 0; j < n; j++) {
            // compute f(X, j)
            if(!((i >> j) & 1))
                // node j is not in X
                continue;
            l = (i ^ (1 << j)); // X \ {j}
            if(!l)
                // X \ {j} == {} empty set
                continue;
            key = (j << 18) + i;
            for(k = 0; k < n; k++) {
                // consider subset X \ {j}
                // where last visited node is k
                if(!((l >> k) & 1))
                    // node k is not in the set
                    continue;
                // do dijkstra between k, j using nodes in X + {s}
                // f(X \ {j}, k) + dijkstra(k, j)
                mask = (i | (1 << s));
                d = dijkstra(cost, adj, j, k, mask);
                // compute f(X \ {j}, k) + d(k, j)
                d = memo[(k << 18) + l] + d;
                // memoize f(X, j) = f(X \ {j}, k) + d(k, j)
                memo[key] = min(memo[key], d);
            }
        }
    }
    ll o = numeric_limits<ll>::max();
    mask = (1 << n) - 1;
    for(i = 0; i < n; i++) {
        d = dijkstra(cost, adj, i, s, mask);
        key = (1 << n) - 1 + (i << 18);
        d = memo[key] + d;
        o = min(d, o);
    }
    cout << o << endl;

    return 0;
}

