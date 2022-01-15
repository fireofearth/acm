#include<bits/stdc++.h>
using namespace std;

/**
Projects are numbered 1..n where each project A can have
one ore more dependencies with another project B_1,...,
B_N that have to be completed before A can be completed
Given a list of projects and their dependencies,
print a sequence of projects to complete such that at
each step a project's dependencies are fulfilled.

Input:
line 1 are two integers n m where 1 <= n is number of
    projects and 0 <= m is the number of dependencies 
line 2..(m+1) are two integers i j between 1 and n
    for projects i, j where j depends on i

Output:
line 1 are n integers of projects in doable order, or
output -1 if no such order exists.

g++ -std=c++11 projects.cpp -o k

Examples:

3 0
o: 1 2 3

3 1
2 1
o: 2 3 1

5 5
1 2
3 2
3 5
2 5
4 5
o1: 1 3 4 2 5
o1: 3 4 1 2 5

3 3
1 2
2 3
3 1
o: -1

7 7
1 3
2 5
3 5
3 4
4 6
4 7
5 7

*/
int main() {
    int i, j, k;
    int n, m;
    cin >> n;
    cin >> m;
    vector<vector<int>> g(n);
    vector<int> count(n);
    queue<int> q;
    vector<int> o;
    for(k = 0; k < m; k++) {
        cin >> i;
        cin >> j;
        // i -> j
        // here we want to make project indices zero indexed for the graph
        i -= 1; j -= 1;
        g[i].push_back(j);
        // increment j's incoming edges
        count[j] += 1;
    }

    for(k = 0; k < n; k++) {
        // add projects with no dependencies to the output sequence first
        if(count[k] == 0) {
            q.push(k);
        }
    }
    while(!q.empty()) {
        i = q.front();
        o.push_back(i);
        for(int j : g[i]) {
            count[j]--;
            if(count[j] == 0)
                q.push(j);
        }
        q.pop();
    }
    if(o.size() != g.size()) {
        cout << "-1" << endl;
        return 0;
    }

    for(k = 0; k < n; k++) {
        cout << o[k] + 1;
        if(k == n - 1) cout << endl;
        else cout << " ";
    }

    return 0;
}
