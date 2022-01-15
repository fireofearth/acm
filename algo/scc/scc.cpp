#include <bits/stdc++.h>
using namespace std;

const int N = 200000;
int low[N], vis[N], scomp[N], scompNum, I;
vector<int> adj[N];
stack<int> verts;
void scc(int u) {
    low[u] = vis[u] = ++I;
    verts.push(u);
    for (int v : adj[u]) {
        if (!vis[v])
            scc(v);
        if (scomp[v] == -1)
            low[u] = min(low[u], low[v]);
    }
    if (vis[u] <= low[u]) {
        int v;
        do {
            v = verts.top();
            verts.pop();
            scomp[v] = scompNum;
        } while (v != u);
        ++scompNum;
    }
}

void get_scc(int n) {
    memset(vis,0,sizeof vis);
    memset(scomp,-1,sizeof scomp);
    scompNum=I=0;
    for (int i=0; i<n; ++i)
        if (!vis[i]) scc(i);
}

/*
Strongly Connected Components
Seems to be correct based on checking with GeeksForGeeks
but leads to runtime error when submitted to the judge
g++ -std=c++11 scc.cpp -o k1
*/
int main() {
    int n; // nodes
    int m; // edges
    int i, j, k;
    int u, v, curr;

    // construct directed graph
    cin >> n >> m;
    if(n == 0) {
        cout << endl;
        return 0;
    }
    //vector<vector<int>> adj(n);
    for(i = 0; i < m; i++) {
        cin >> u >> v; // edge u -> v
        u -= 1; v -= 1;
        adj[u].push_back(v);
    }

    // Find SCC using
    // UBC code archive algorithm
    get_scc(n);

    cout << scompNum << endl;
    for(i = 0; i < n; i++) {
        cout << scomp[i];
        if(i < n - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
