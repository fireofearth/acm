#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

/*
Strongly Connected Components
Iterative algorithm
g++ -std=c++11 iter-scc.cpp -o k2
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
    vector<vector<int>> adj(n);
    for(i = 0; i < m; i++) {
        cin >> u >> v; // edge u -> v
        u -= 1; v -= 1;
        adj[u].push_back(v);
    }

    //Find SCC using iterative DFS
    stack<int> s; // for recusing DFS iteratively
    stack<int> t; // for backtrack DFS iteratively
    stack<int> z; // for adding to SCC
    vector<int> indices(n, -1); // index of discovery
    vector<int> lowests(n, -1); // lowest index observed
    vector<int> comp(n, -1); // component of node
    int index = 0; // index to set each node
    int compi = 0; // component to set each node
    for(i = 0; i < n; i++) {
        if(indices[i] != -1) continue;
        s.push(i);
        while(!s.empty()) {
            // get next node
            u = s.top(); s.pop();
            if(indices[u] == -1) {
                // if node is unvisited
                // we cannot check that node has been visited before recursive call
                // we can ONLY check that node has been visited within the call
                lowests[u] = indices[u] = index; index++;
                z.push(u);

                // recurse DFS
                for(int v : adj[u]) {
                    s.push(v);
                    t.push(u);
                }
                if(t.empty() || u != t.top()) t.push(u);
                if(adj[u].size() > 0) continue;
            }

            // backtrack DFS
            while(!t.empty()) {
                u = t.top(); t.pop();
                // only want to backtrack on u when all edges from u has been recursed
                // this can be done by adding same node to stack multiple times to keep track of how many recursive calls have been made
                if(!t.empty() && u == t.top()) break;
                for(int v : adj[u])
                    if(comp[v] == -1) {
                        lowests[u] = min(lowests[u], lowests[v]);
                    }
                if(indices[u] <= lowests[u]) {
                    do {
                        v = z.top(); z.pop();
                        comp[v] = compi;
                    } while(u != v);
                    compi++;
                }
            }
        }
    }
    
    cout << compi << endl;
    for(i = 0; i < n; i++) {
        cout << comp[i];
        if(i < n - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
