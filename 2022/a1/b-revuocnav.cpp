#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

/*
Shortest Path via Dijkstra
g++ -std=c++11 b-revuocnav.cpp -o k
*/

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; // nodes
    int m; // edges
    cin >> n >> m;
    int s; // start node
    cin >> s;
    s -= 1;
    int i, j, k;
    ll c;
    // build graph
    vector<vector<int>> adj(n); // adj list
    // weights are 0 ... 10^9 = 1000000000
    vector<vector<ll>> w(n); // weights of edges
    vector<bool> v(n); // visited
    vector<ll> d(n); // shortest distance from s
    for(i = 0; i < n; i++) {
        d[i]   = -1;
    }
    for(i = 0; i < m; i++) {
        cin >> j >> k >> c;
        j -= 1; k -= 1;
        adj[j].push_back(k);
        adj[k].push_back(j);
        w[j].push_back(c);
        w[k].push_back(c);
    }
    
    // do Dijkstra
    priority_queue<
        pair<ll, int>, // type to store - cost, node
        vector<pair<ll, int>>, // underlyting container
        greater<pair<ll, int>> // comparator
    > q;
    q.push({0, s});
    while(!q.empty()) {
        tie(c, i) = q.top(); q.pop();
        if(v[i]) continue;
        v[i] = true;
        d[i] = c;
        for(j = 0; j < adj[i].size(); j++)
            q.emplace(w[i][j] + c, adj[i][j]);
    }

    printv(d);
    return 0;
}

