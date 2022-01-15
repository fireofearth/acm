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
    int floor;
    ll time;
    bool found_g, found_s;
    set<int, greater<int>> hvals;


    // build graph
    vector<vector<int>> adj(n, vector<int>()); // adj list
    vector<vector<ll>> ts(n, vector<ll>()); // time to travel edge
    vector<vector<int>> hs(n, vector<int>()); // number of floors descended to travel edge
    vector<bool> v(n); // visited nodes while traveling
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
        if(h < init_floor)
            hvals.insert(h);
    }
    cin >> s >> g;
    s -= 1; g -= 1;


    // do Dijkstra for each value of h
    priority_queue<
        tuple<ll, int, int>, // type to store - time, floor, node
        vector<tuple<ll, int, int>>, // underlyting container
        greater<tuple<ll, int, int>> // comparator
    > q;
    for(int max_h : hvals) {
        found_g = false;
        found_s = false;

        cout << "here " << max_h << endl;

        // Dijkstra to travel from s to g
        fill(v.begin(), v.end(), false);
        q.emplace(0, init_floor, s);
        while(!q.empty()) {
            tie(time, floor, i) = q.top(); q.pop();
            // went past ground floor
            if(floor < 1) continue;
            // found goal
            if(i == g) {
                found_g = true;
                break;
            }
            if(v[i]) continue;
            v[i] = true;
            for(j = 0; j < adj[i].size(); j++) {
                if(hs[i][j] <= max_h)
                    q.emplace(ts[i][j] + time, floor - hs[i][j], adj[i][j]);
            }
        }
        while(!q.empty()) q.pop();
        if(!found_g) continue; // try smaller h values
        
        cout << "found g" << endl;

        // Dijkstra to travel from g to s
        fill(v.begin(), v.end(), false);
        q.emplace(time, floor, g);
        while(!q.empty()) {
            tie(time, floor, i) = q.top(); q.pop();
            // went past ground floor
            if(floor < 1) continue;
            // found start
            if(i == s) {
                found_s = true;
                break;
            }
            if(v[i]) continue;
            v[i] = true;
            for(j = 0; j < adj[i].size(); j++) {
                if(hs[i][j] <= max_h)
                    q.emplace(ts[i][j] + time, floor - hs[i][j], adj[i][j]);
            }
        }

        if(found_s) break; // went to g and back to s without going past ground floor
        while(!q.empty()) q.pop();
    }

    if(found_s) {
        return time;
    } else {
        return -1;
    }
}

/*
Shortest Path via Dijkstra
This is an incorrect implementation
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

