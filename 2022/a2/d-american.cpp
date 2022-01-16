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

bool DEBUG = false;

ll dijkstra(
    vector<vector<ll>> &cost,
    vector<vector<ll>> &adj,
    int k, int j, int mask
) {
    // dijkstra k => j
    priority_queue<
        pair<ll, int>, // cost, node
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > q;
    int u, v, i;
    ll d;
    q.emplace(0, k);
    while(!q.empty()) {
        tie(d, u) = q.top(); q.pop();
        if(u == j) return d;
        if(!((mask >> u) & 1)) continue;
        mask = mask ^ (1 << u);
        for(int v : adj[u]) {
            if(!((mask >> v) & 1)) continue;
            q.emplace(d + cost[u][v], v);

        }
    }
    return numeric_limits<ll>::max();
}

/*
Traveling Salesman Problem with bitmasks
g++ -std=c++11 d-american.cpp -o k

Graph is undirected.

inputs:
n, m - number of nodes, edges. 2 <= n <= 18
for each 1..m lines
> u, v, d - edge (u, v) with cost d. d <= 10^7
s - start node

outputs:
cost to traverse all nodes starting from s

facts about numbers:
18 < 32 and 32 == 2^5
2^18 = 262,144
5 + 18 = 23 so we need an array memoizing at most 2^23 numbers
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    int n, m;
    int i, j, k, l;
    int u, v, s;
    int mask, key, key2;
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
    s -= 1;
    vector<ll> memo((1 << 23), numeric_limits<ll>::max());
    for(i = 0; i < n; i++) {
        // node i
        cost[i][i] = 0;
        key = (i << 18) + (1 << i); // f({i}, i) = 0;
        memo[key] = cost[s][i];
        //cout << "key " << bitset<32>(key) << " memo " << memo[key] << endl;
    }

    for(i = 1; i < (1 << n); i++) {
        // iterate over subsets X where bitmasks equal i
        if((i >> s) & 1)
            // X contains s
            continue;
        if(DEBUG) cout << "set X        " << bitset<32>(i) << endl;
        for(j = 0; j < n; j++) {
            // compute f(X, j)
            if(!((i >> j) & 1))
                // node j is not in X
                continue;
            l = (i ^ (1 << j)); // X \ {j}
            if(DEBUG) cout << "set X - j    " << bitset<32>(l) << " j=" << j+1 << endl;
            if(!l)
                // X \ {j} == {} empty set
                continue;
            key = (j << 18) + i; // (X, j)
            if(DEBUG) cout << "key (X, j)   " << bitset<32>(key) << " j=" << j+1 << endl;
            for(k = 0; k < n; k++) {
                // consider subset X \ {j} where last visited node is k
                if(!((l >> k) & 1))
                    // node k is not in the set
                    continue;
                key2 = (k << 18) + l; // (X \ {j}, k)
                if(DEBUG) cout << "key (X-j, k) " << bitset<32>(key2) << " k=" << k+1 << endl;
                // compute f(X \ {j}, k) + d(k, j)
                if(DEBUG) printf("k=%d -> j=%d: f(X-j, k)=%lld \n", k+1, j+1, memo[key2]);
                if(memo[key2] == numeric_limits<ll>::max())
                    // no way to traverse X \ {j} and end up at k
                    continue;
                mask = (i | (1 << s)); // X U {s}
                d = dijkstra(cost, adj, k, j, mask);
                if(d == numeric_limits<ll>::max())
                    // no way to traverse k -> j
                    continue;
                d += memo[key2];
                // memoize f(X, j) = f(X \ {j}, k) + dijkstra(k, j)
                memo[key] = min(memo[key], d);
            }
            if(DEBUG) printf("j=%d: f(X, j)=%lld \n", j+1, memo[key]);
        }
    }

    if(DEBUG) cout << endl << "output" << endl;
    ll o = numeric_limits<ll>::max();
    for(i = 0; i < n; i++) {
        // last node visited is i
        if(i == s)
            // i is start node
            continue;
        key = (((1 << n) - 1) ^ (1 << s)) + (i << 18); // f(X, i)
        if(DEBUG) cout << "key       " << bitset<32>(key) << endl;
        if(memo[key] == numeric_limits<ll>::max())
            // no way to traverse X and end up at i
            continue;
        mask = ((1 << n) - 1);
        d = dijkstra(cost, adj, i, s, mask);
        if(d == numeric_limits<ll>::max())
            // no way to traverse i -> s
            continue;
        d += memo[key];
        o = min(d, o);
    }

    cout << o << endl;

    return 0;
}

