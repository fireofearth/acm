#include <bits/stdc++.h>
using namespace std;

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
Union-Find and Floyd-Warshall
Too slow
g++ -std=c++11 d-knives.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; // nodes
    int m; // edges
    cin >> n >> m;

    int i, j, k;
    int a, b;
    // Initialize Union-Find and Adj Mtx
    vector<vector<bool>> adj(n, vector<bool>(n)); // adj-mtx
    vector<int> parents(n);
    vector<int> ranks(n);
    for(i = 0; i < n; i++) {
        parents[i] = i;
        adj[i][i]  = true;
    }

    for(i = 0; i < m; i++) {
        cin >> a >> b; // a => b
        a -= 1; b -= 1;
        adj[a][b] = true;
    }

    // Floyd-Warshall
    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++) {
                adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
            }

    // Union
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) {
            if(adj[i][j] && adj[j][i])
                join(parents, ranks, i, j);
        }

    // Find
    for(i = 0; i < n; i++) {
        a = find(parents, i);
        a += 1;
        cout << a;
        if(i != n - 1)
            cout << " ";
    }
    cout << endl;

    return 0;
}

