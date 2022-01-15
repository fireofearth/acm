#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int find(vector<int> &parents, int i) {
    if(parents[i] != i) {
        parents[i] = find(parents, parents[i]);
    }
    return parents[i];
}

void join(vector<int> &parents, vector<int> &ranks, int a, int b) {
    a = find(parents, a);
    b = find(parents, b);
    if(a == b) return;
    if (ranks[a] > ranks[b])
        parents[b] = a;
    else if(ranks[b] > ranks[a])
        parents[a] = b;
    else {
        parents[b] = a;
        ranks[a]++;
    }
}

/*
DFS for cycle detection and Kruskal MST
g++ -std=c++11 f-network.cpp -o k
*/
string test() {
    int n; // nodes
    int m; // edges
    cin >> n >> m;

    int i, j, k;
    int u, v, w;
    char c;
    int cost = 0;
    priority_queue<
        tiii, // store - cost, to node, from node
        vector<tiii>,
        greater<tiii>
    > q;

    // Construct graph
    vector<vector<int>> adj(n); // adj-list
    vector<vector<int>> weight(n); // adj-list
    vector<int> parents(n); // for union-find
    vector<int> ranks(n); // for union-find
    for(i = 0; i < n; i++) {
        parents[i] = i;
    }
    for(i = 0; i < m; i++) {
        cin >> c >> u >> v >> w;
        // add required 'B' to adj list of subgraph
        // add not required edges to priority queue
        if(c == 'B') {
            adj[u].push_back(v);
            adj[v].push_back(u);
            weight[u].push_back(w);
            weight[v].push_back(w);
        } else q.push({w, u, v});
    }

    // do cycle detection on required 'B' edges
    // also compute costs of these edges
    // and obtain the connectivity of the edges
    bool has_cycle = false;
    vector<bool> visited(n);
    stack<pii> todo; // store - current node, last node
    for(i = 0; i < n; i++) {
        if(visited[i]) continue;
        // check cycle in component containing node i
        todo.push({i, -1});
        while(!todo.empty()) {
            int curr, last;
            tie(curr, last) = todo.top(); todo.pop();
            if(visited[curr]) {
                has_cycle = true;
                break;
            }
            visited[curr] = true;
            for(j = 0; j < adj[curr].size(); j++) {
                if(adj[curr][j] == last) continue; // backwards edge
                cost += weight[curr][j];
                join(parents, ranks, adj[curr][j], curr);
                todo.push({adj[curr][j], curr});
            }
        }
        if(has_cycle) break;
    }
    if(has_cycle) {
        return "NOPE";
    }
    
    // do Kruskal MST
    while(!q.empty()) {
        tie(w, u, v) = q.top(); q.pop();
        if(find(parents, u) == find(parents, v)) continue;
        join(parents, ranks, u, v);
        cost += w;
    }

    bool is_incomplete = false;
    u = find(parents, 0);
    for(i = 0; i < n; i++)
        if(find(parents, i) != u)
            is_incomplete = true;

    if(is_incomplete) {
        return "NOPE";
    }

    return to_string(cost);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, T;
    cin >> T;
    vector<string> ans;
    ans.reserve(T);
    for(i = 0; i < T; i++) ans.push_back(test());
    for(i = 0; i < T; i++) cout << ans[i] << endl;

    return 0;
}

