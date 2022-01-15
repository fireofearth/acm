#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool DEBUG = false;


ll test() {
    int init_floor; // starting floor
    int n; // nodes
    int m; // edges
    int s; // start node
    int g; // goal node
    cin >> init_floor >> n >> m;
    int i, j, k;
    int a, b, h;
    ll t;

    // build graph
    vector<vector<int>> adj(n); // adj list
    vector<vector<ll>> ts(n); // time to travel edge
    vector<vector<int>> hs(n); // number of floors descended to travel edge
    // visited (floor, node) while traveling s -> g
    vector<vector<bool>> vt(init_floor + 1, vector<bool>(n)); 
    // visited (floor, node) while traveling g -> s
    vector<vector<bool>> vf(init_floor + 1, vector<bool>(n));
    for(i = 0; i < m; i++) {
        // edge (a, b) takes time t, descend h floors
        cin >> a >> b >> t >> h;
        a -= 1; b -= 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
        ts[a].push_back(t);
        ts[b].push_back(t);
        hs[a].push_back(h);
        hs[b].push_back(h);
    }
    cin >> s >> g;
    s -= 1; g -= 1;

    // Dijkstra to travel from s -> g -> s
    // time, direction, floor, node
    priority_queue<
        tuple<ll, bool, int, int>, // type to store
        vector<tuple<ll, bool, int, int>>, // underlyting container
        greater<tuple<ll, bool, int, int>> // comparator smallest
    > q;
    int floor;
    ll time;
    bool dir;
    bool found = false;
    if(DEBUG) printf("going %d -> %d -> %d \n", s, g, s);
    // direction: true (to) means s -> g, false (from) means g -> s;
    q.emplace(0, true, init_floor, s);
    while(!q.empty()) {
        tie(time, dir, floor, i) = q.top(); q.pop();
        // if went past ground floor
        if(floor < 1) continue;
        // found goal
        if(dir == true && i == g) dir = false;
        if(DEBUG) printf("i=%d floor=%d dir=%d time=%d \n", i, floor, dir, time);
        if(dir == false && i == s) {
            found = true;
            break;
        }
        if(dir == true) {
            if(vt[floor][i]) continue;
            vt[floor][i] = true;
        } else { // dir == false
            if(vf[floor][i]) continue;
            vf[floor][i] = true;
        }
        for(j = 0; j < adj[i].size(); j++) {
            //printf("edge 5d \n", adj[i][j]);
            q.emplace(ts[i][j] + time, dir, floor - hs[i][j], adj[i][j]);
        }
    }
    
    if(found) {
        return time;
    } else {
        return -1;
    }
}

/*
Shortest Path via Dijkstra
g++ -std=c++11 j-escape.cpp -o k
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }
    int T, i;
    cin >> T;
    vector<ll> ans(T);
    for(int i = 0; i < T; i++) {
        ans[i] = test();
    }
    for(int a : ans)
        cout << a << endl;
    return 0;
}

