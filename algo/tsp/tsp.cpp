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
Traveling Salesman Problem with 
g++ -std=c++11 tsp.cpp -o k

Graph is undirected.

inputs:
n, m - number of nodes, edges. 2 <= n <= 18
for each 1..m lines
> u, v, d - edge (u, v) with cost d. d <= 10^7
s - start node

outputs:
cost to traverse all nodes starting from s, or -1 if not possible
the list of nodes traversed if possible

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
                if(cost[k][j] == numeric_limits<ll>::max())
                    // no way to traverse edge (k, j)
                    continue;
                d = memo[key2] + cost[k][j];
                // memoize f(X, j) = f(X \ {j}, k) + d(k, j)
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
        if(cost[i][s] == numeric_limits<ll>::max())
            // no way to traverse edge (i, s)
            continue;
        d = memo[key] + cost[i][s];
        o = min(d, o);
    }

    if(o == numeric_limits<ll>::max()) {
        cout << -1 << endl;
    } else {
        cout << o << endl;

        vector<int> seq;
        seq.push_back(s + 1);
        mask = ((1 << n) - 1) ^ (1 << s);
        if(DEBUG) cout << "mask      " << bitset<32>(mask) << endl;
        while(mask) {
            d = numeric_limits<ll>::max();
            u = -1;
            for(i = 0; i < n; i++) {
                if(i == s) continue;
                if(!((mask >> i) & 1)) continue;
                key = mask + (i << 18);
                if(DEBUG) cout << "key       " << bitset<32>(key) << endl;
                if(d > memo[key]) {
                    u = i;
                    d = memo[key];
                }
            }
            if(u == -1)
                throw runtime_error("solution: can't node in traversal");
            mask = mask ^ (1 << u);
            seq.push_back(u + 1);
        }
        seq.push_back(s + 1);
        reverse(seq.begin(), seq.end());
        printv(seq);
    }
    
    return 0;
}

