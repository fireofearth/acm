#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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
g++ -std=c++17 -o k b-revuocnav.cpp

cat ../../a1/tests/b-revuocnav-1.{in,out}
./k < ../../a1/tests/b-revuocnav-1.in
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i;
    int n; // intersections
    int m; // roads
    ll s; // start
    ll u, v; // edge
    ll c; // cost
    cin >> n >> m;
    cin >> s;
    vector<vector<pll>> g(n); // adj list graph
    vector<bool> visited(n, false);
    vector<ll> cost(n, -1);
    s -= 1;
    for (i = 0; i < m; i++) {
        cin >> u >> v >> c;
        u -= 1;
        v -= 1;
        g[u].push_back(make_pair(v, c));
        g[v].push_back(make_pair(u, c));
    }

    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.push(make_pair(s, 0));
    while (!q.empty()) {
        tie(u, c) = q.top(); q.pop();
        cost[u] = c;
        visited[u] = true;
        for (auto [v, c_travel] : g[u]) {
            if (visited[v]) {
                continue;
            }
            
            q.push(make_pair(v, cost[u] + c_travel));
        }
    }

    printv(cost);
    return 0;
}

