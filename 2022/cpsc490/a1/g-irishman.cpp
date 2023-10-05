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

bool DEBUG = false;

void dfs(
    vector<vector<int>> &adj,
    vector<vector<ll>> &time_beg,
    vector<vector<ll>> &time_end,
    ll &counter,
    int u
) {
    if(DEBUG) printf("node=%d, counter=%d\n", u + 1, counter);
    time_beg[u].push_back(counter);
    counter++;
    // recursive call
    for(int v : adj[u]) {
        dfs(adj, time_beg, time_end, counter, v);
    }
    time_end[u].push_back(counter);
    counter++;
}

void test(vector<vector<string>> &ans, int t) {
    int N; // nodes 10^5
    int Q; // queries 10^5
    int i, j, k;
    int u, v, x, y;
    cin >> N >> Q;

    vector<vector<int>> adj(N); // adj-list
    vector<bool> is_start(N, true);
    vector<vector<ll>> time_beg(N);
    vector<vector<ll>> time_end(N);

    // anc[i][j] => i is ancestor of j
    // i -> ... -> j
    //vector<vector<bool>> anc(N, vector<bool>(N)); 

    // record N - 1 edges
    for(i = 0; i < N - 1; i++) {
        // u is the direct ancestor of v; u -> v
        cin >> u >> v;
        u -= 1; v -= 1;
        adj[u].push_back(v);
        is_start[v] = false;
        //anc[u][v] = true;
        //anc[i][i] = true;
    }
    //anc[N - 1][N - 1] = true;

    // record Q questions
    vector<pii> qs(Q);
    for(i = 0; i < Q; i++) {
        cin >> x >> y; // x is an ancestor of y?
        x -= 1; y -= 1;
        qs[i] = {x, y};
    }

    if(DEBUG) cout << "starting DFS" << endl;
    int curr;
    ll counter = 0;
    for(i = 0; i < N; i++) {
        if(!is_start[i]) continue;
        if(DEBUG) printf("starting DFS at %i\n", i + 1);
        dfs(adj, time_beg, time_end, counter, i);
    }
    if(DEBUG) {
        cout << "time_beg" << endl;
        for(i = 0; i < N; i++) {
            printf("node=%d sz=%d: \n", i + 1, time_beg[i].size());
            printv(time_beg[i]);
        }
        cout << "time_end" << endl;
        for(i = 0; i < N; i++) {
            printf("node=%d sz=%d: \n", i + 1, time_end[i].size());
            printv(time_end[i]);
        }
    }

    // answer questions with memoized ancestry
    int xbeg, xend, ybeg, yend;
    ans[t] = vector<string>(Q);
    for(i = 0; i < Q; i++) {
        //cin >> x >> y; // x is an ancestor of y?
        //x -= 1; y -= 1;
        tie(x, y) = qs[i];
        xbeg = time_beg[x][0];
        for(k = 0; k < time_beg[y].size(); k++) {
            if(xbeg < time_beg[y][k])
                break;
        }
        ybeg = time_beg[y][k];
        xend = time_end[x][0];
        yend = time_end[y][k];
        if(xbeg < ybeg && yend < xend)
            ans[t][i] = "yes";
        else
            ans[t][i] = "no";
    }
}

/*
Level order traversal and memoize
g++ -std=c++11 g-irishman.cpp -o k
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }
    int i, T;
    cin >> T;
    vector<vector<string>> ans(T);
    for(i = 0; i < T; i++) test(ans, i);
    for(vector<string> _ans : ans)
        for(string a : _ans)
            cout << a << endl;

    return 0;
}

