#include <bits/stdc++.h>
using namespace std;

bool DEBUG = false;

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
Topological Sort
g++ -std=c++11 c-neimoidia.cpp -o k
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if(argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    int n; // nodes
    int m; // edges
    cin >> n >> m;
    vector<int> d(n); // in-degrees
    int i, j, k;
    int a, b;
    // build graph
    vector<vector<int>> adj(n); // adj list
    for(i = 0; i < n; i++) {
        adj[i] = vector<int>();
    }
    for(i = 0; i < m; i++) {
        cin >> a >> b; // a < b
        adj[a].push_back(b);
        d[b] += 1;
    }

    // solve using Topological Sort
    vector<int> o;
    priority_queue<
        int, // type to store - node of in-degree 0
        vector<int>, // underlying container
        greater<int> // comparator
    > q;
    for(i = 0; i < n; i++) {
        if(d[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        i = q.top(); q.pop();
        o.push_back(i);
        for(j = 0; j < adj[i].size(); j++) {
            k = adj[i][j];
            d[k] -= 1;
            if(d[k] == 0) q.push(k);
        }
    }

    if(o.size() != n)
        cout << "*" << endl;
    else {
        if(DEBUG) {
            printv(o);
        } else {
            for(int k : o)
                cout << k << endl;
        }
    }

    return 0;
}

