#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<lld>::max();

/*
Finding the longest path by doing topological sort
and do DP on each node in the list: the length of the
longest path that ends at the node in the list.

g++ -std=c++11 g-longest.cpp -o k
*/
int main() {
    int i;
    int N, M, x, y;
    cin >> N >> M;
    // edges of graph
    vector<vector<int>> f(N);
    // reversed edges of graph
    vector<vector<int>> b(N);
    // n_incoming[i] number of incoming eddges to node i
    vector<int> n_incoming(N);
    // list of topological sort
    vector<int> m;
    // l[i] length of longest path to node i
    vector<int> l(N);

    for(i = 0; i < M; i++) {
        cin >> x >> y; x--; y--;
        f[x].push_back(y);
        b[y].push_back(x);
        n_incoming[y] += 1;
    }
    
    queue<int> q;
    for(i = 0; i < N; i++) {
        if(n_incoming[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        i = q.front(); q.pop();
        m.push_back(i);
        for(int j : f[i]) {
            n_incoming[j]--;
            if(n_incoming[j] == 0) q.push(j);
        }
    }

    int longest = 0;
    for(i = 0; i < N; i++) {
        int j = m[i];
        l[j] = 0;
        for(int k : b[j]) {
            l[j] = max(l[j], l[k] + 1);
        }
        longest = max(l[j], longest);
    }
    cout << longest << endl;

    return 0;
}
/*
samples

5 8
5 3
2 3
2 4
5 2
5 1
1 4
4 3
1 3

out: 3

4 5
1 2
1 3
3 2
2 4
3 4

out: 3

6 3
2 3
4 5
5 6

out: 2

9 12
4 5
3 6
5 6
2 9
2 5
5 8
3 5
6 8
2 4
5 7
7 9
1 3

out: 4
*/
