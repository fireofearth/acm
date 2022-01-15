#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool check_has_path_starting_at(vector<vector<char>> &m,
        vector<vector<int>> &visited, string s,
        int p, int l, int h, int i, int j) {
    // l - length of matrix
    // h - height of matrix
    // i - row of matrix
    // j - column of matrix
    if(s[0] != m[i][j]) return false;
    //printf("checking (%d, %d)\n", i, j);

    visited[i][j] = p;
    pii cell = make_pair(i, j);
    stack<pii> route;
    route.push(cell);
    while(!route.empty()) {
        cell = route.top();
        i = cell.first;
        j = cell.second;
        //printf(" (%d, %d), %c\n", i, j, m[i][j]);
        if(route.size() == s.size()) {
            // check if we found a path or need to backtrack
            if((i == 0) || (i == h - 1) || (j == 0) || (j == l - 1)) {
                return true;
            } else {
                route.pop();
            }
        } else {
            // go to the next cell in the route
            if(i < h - 1 && visited[i + 1][j] != p && s[route.size()] == m[i + 1][j]) {
                visited[i + 1][j] = p;
                route.push(make_pair(i + 1, j));

            } else if(0 < i && visited[i - 1][j] != p && s[route.size()] == m[i - 1][j]) {
                visited[i - 1][j] = p;
                route.push(make_pair(i - 1, j));

            } else if(j < l - 1 && visited[i][j + 1] != p && s[route.size()] == m[i][j + 1]) {
                visited[i][j + 1] = p;
                route.push(make_pair(i, j + 1));
            } else if(0 < j && visited[i][j - 1] != p && s[route.size()] == m[i][j - 1]) {
                visited[i][j - 1] = p;
                route.push(make_pair(i, j - 1));
            } else {
                route.pop();
            }
        }
    }
    
    return false;
}

bool check_has_path(vector<vector<char>> &m,
        vector<vector<int>> &visited,
        string s, int l, int h) {
    int p = 1;
    // check paths starting at edges of matrix
    for(int i = 0; i < h; i++) {
        // check all left edges
        if(check_has_path_starting_at(m, visited, s, p, l, h, i, 0))
            return true;
        p++;
    }

    for(int i = 0; i < h; i++) {
        // check all right edges
        if(check_has_path_starting_at(m, visited, s, p, l, h, i, l - 1))
            return true;
        p++;
    }

    for(int j = 1; j < l - 1; j++) {
        // check rest top edges
        if(check_has_path_starting_at(m, visited, s, p, l, h, 0, j))
            return true;
        p++;
    }

    for(int j = 1; j < l - 1; j++) {
        // check rest top edges
        if(check_has_path_starting_at(m, visited, s, p, l, h, h - 1, j))
            return true;
        p++;
    }

    return false;
}

/**

g++ -std=c++11 str_path_matrix.cpp -o k

Examples:
4 3
abce
sfcs
adee
bcced

4 4
xyxx
zyyz
zzyz
xzyx
yyyyy
-> true

5 4
xzyxx
zzyyx
xzzyx
xxzyx
zzz
-> true
zzz, zzzzz are the only length of z strings that works
yyyyy is the only length of y strings that works

5 4
xzyxx
zzyyx
xzzyx
xxzyx
xzzyy

5 5
aaaaa
abbba
bbabb
abbba
aaaaa
bbbbbbb
-> true
bbbbbbb is the only length of b strings that works

*/
int main() {
    int l, h, p;
    string s, t;
    cin >> l >> h;
    vector<vector<char>> m(h);
    vector<vector<int>> visited(h);
    for(int i = 0; i < h; i++) {
        cin >> t;
        m[i] = vector<char>(l);
        visited[i] = vector<int>(l, 0);
        for(int j = 0; j < l; j++) {
            m[i][j] = t[j];
        }
    }
    cin >> s;
    
    if(check_has_path(m, visited, s, l, h)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    return 0;
}
