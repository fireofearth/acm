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

void subproblem(
    vector<int> &memo,
    vector<vector<int>> &tree,
    vector<vector<int>> &weights,
    int curr, int n
) {
    if(tree[curr].size() == 0) {
        memo[curr] = 0;
        return;
    }
    int i, j, k;
    int u, v;
    for(int i : tree[curr]) {
        subproblem(memo, tree, weights, i, n);
    }
    int max_weight = 0;
    int acc_weight;
    // weight gained by placing an edge from curr to a neighbor
    for(i = 0; i < tree[curr].size(); i++) {
        // If weight is not positive, there is no value adding it
        if(weights[curr][i] <= 0) continue;
        // u; place edge (curr, u)
        u = tree[curr][i];
        acc_weight = weights[curr][i];
        //printf("%d %d %d \n", curr, u, acc_weight);
        for(j = 0; j < tree[curr].size(); j++) {
            if(i == j) continue;
            // v; skip edge (curr, v)
            v = tree[curr][j];
            acc_weight += memo[v];
        }
        for(j = 0; j < tree[u].size(); j++) {
            // v; skip edge (u, v)
            v = tree[u][j];
            acc_weight += memo[v];
        }
        if(acc_weight > max_weight)
            max_weight = acc_weight;
    }
    // weight gein by not placing an edge from curr
    acc_weight = 0;
    for(i = 0; i < tree[curr].size(); i++) {
        u = tree[curr][i];
        acc_weight += memo[u];
    }
    if(acc_weight > max_weight)
        max_weight = acc_weight;
    memo[curr] = max_weight;
}

/*
Tree DP memoizing past traversals.
g++ -std=c++11 c-marriage.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, j, k;
    int n; // 10^5 nodes
    cin >> n;
    int u, v, w;
    // 10^5 edges
    vector<vector<int>> adj(n);
    vector<vector<int>> _weights(n);
    for(i = 0; i < n - 1; i++) {
        cin >> u >> v >> w; // edge u-v with profit w
        u -= 1;
        v -= 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
        _weights[u].push_back(w);
        _weights[v].push_back(w);
    }

    // Build Tree using BFS
    vector<vector<int>> tree(n);
    vector<vector<int>> weights(n);
    vector<bool> visited(n);
    queue<int> q;
    visited[0] = true;
    q.push(0);
    while(!q.empty()) {
        u = q.front(); q.pop();
        for(i = 0; i < adj[u].size(); i++) {
            v = adj[u][i];
            if(visited[v]) continue;
            visited[v] = true;
            tree[u].push_back(v);
            //printf("%d %d %d \n", u, v, _weights[u][i]);
            weights[u].push_back(_weights[u][i]);
            q.push(v);
        }
    }
    
    // Tree DP
    vector<int> memo(n);
    subproblem(memo, tree, weights, 0, n);

    cout << memo[0] << endl;
    //printv(memo);
    return 0;
}

