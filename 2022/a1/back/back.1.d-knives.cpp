#include <bits/stdc++.h>
using namespace std;

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
Strongly Connected Components using Tarjan's Algorithm
This fails because the guard if(indices[v] == -1)
can get invalidated after a recursive call.
This is fixed in a followup submission
g++ -std=c++11 d-knives.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
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
    int compi = 1; // component to set each node
    bool backtrack;
    for(i = 0; i < n; i++) {
        if(indices[i] != -1) continue;
        s.push(i);
        while(!s.empty()) {
            backtrack = true;
            // get next node
            u = s.top(); s.pop();
            lowests[u] = indices[u] = index; index++;
            z.push(u);

            // recurse DFS
            for(int v : adj[u]) {
                if(indices[v] == -1) {
                    s.push(v);
                    t.push(u);
                    backtrack = false;
                }
            }
            if(t.empty() || u != t.top()) t.push(u);

            // backtrack DFS
            if(!backtrack) continue;
            while(!t.empty()) {
                u = t.top(); t.pop();
                // only want to backtrack on u when all edges from u has been recursed
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
    
    printv(comp);
    //for(i = 0; i < n; i++) {
    //    cout << comp[i];
    //    if(i < n - 1) cout << " ";
    //}
    //cout << endl;
    return 0;
}

