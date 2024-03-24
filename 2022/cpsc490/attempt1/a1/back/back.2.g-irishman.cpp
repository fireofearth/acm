#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

void test(vector<vector<string>> &ans, int t) {
    int N; // nodes 10^5
    int Q; // queries 10^5
    int i, j, k;
    int u, v, x, y;
    int curr, last;
    cin >> N >> Q;

    vector<vector<int>> adj(N); // adj-list
    vector<bool> is_start(N, true);

    // anc[i][j] => i is ancestor of j
    // i -> ... -> j
    vector<vector<bool>> anc(N, vector<bool>(N)); 

    // record N - 1 edges
    for(i = 0; i < N - 1; i++) {
        // u is the direct ancestor of v; u -> v
        cin >> u >> v;
        u -= 1; v -= 1;
        adj[u].push_back(v);
        is_start[v] = false;
        anc[u][v] = true;
        anc[i][i] = true;
    }
    anc[N - 1][N - 1] = true;

    // record Q questions
    //vector<pii> qs(Q);
    //for(i = 0; i < Q; i++) {
    //    cin >> x >> y; // x is an ancestor of y?
    //    x -= 1; y -= 1;
    //    qs[i] = {x, y};
    //}

    // traverse tree from root to memoize ancestry
    queue<pii> q; // store current node, last node
    for(i = 0; i < N; i++) {
        if(!is_start[i]) continue;
        q.push({i, -1});
        vector<int> record;
        while(!q.empty()) {
            tie(curr, last) = q.front(); q.pop();

            for(j = 0; j < adj[curr].size(); j++)
                q.push({adj[curr][j], curr});

            if(last == -1) continue;

            for(int j : record)
                anc[j][curr] = anc[j][last];
            //for(j = 0; j < N; j++)
            //    if(j != curr && j != last)
            //        anc[j][curr] = anc[j][last];
            record.push_back(last);
        }
    }

    // answer questions with memoized ancestry
    ans[t] = vector<string>(Q);
    for(i = 0; i < Q; i++) {
        cin >> x >> y; // x is an ancestor of y?
        x -= 1; y -= 1;
        //tie(x, y) = qs[i];
        if(anc[x][y]) ans[t][i] = "yes";
        else          ans[t][i] = "no";
    }
}

/*
Level order traversal and memoize
g++ -std=c++11 g-irishman.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, T;
    cin >> T;
    vector<vector<string>> ans(T);
    for(i = 0; i < T; i++) test(ans, i);
    for(vector<string> _ans : ans)
        for(string a : _ans)
            cout << a << endl;

    return 0;
}

