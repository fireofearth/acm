#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool DEBUG = false;

int search(
    vector<string> board,
    pii start, int n, int m
) {
    vector<vector<bool>> visited(n, vector<bool>(m));
    int i, j, _i, _j;
    int tacos = 0;
    queue<pii> q; // stores i, j
    q.push(start);
    // BFS to find tacos not blocked by walls
    while(!q.empty()) {
        tie(i, j) = q.front(); q.pop();
        if(visited[i][j]) continue;
        visited[i][j] = true;
        if(board[i][j] == 'T') tacos += 1;
        vector<pii> moves;
        if(i + 1 <  n) moves.emplace_back(i + 1, j);
        if(j + 1 <  m) moves.emplace_back(i, j + 1);
        if(i - 1 >= 0) moves.emplace_back(i - 1, j);
        if(j - 1 >= 0) moves.emplace_back(i, j - 1);
        for(pii move : moves) {
            tie(_i, _j) = move;
            if(board[_i][_j] != '#')
                q.push(move);
        }
    }

    if(DEBUG) {
        cout << " 0123456789" << endl;
        for(i = 0; i < n; i++) {
            cout << i << board[i] << endl;
        }
        cout << endl;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(visited[i][j]) cout << ".";
                else cout << " ";
            }
            cout << endl;
        }
    }

    // DFS to find tacos blocked by walls
    vector<vector<bool>> _visited(n, vector<bool>(m));
    int _tacos;
    bool _jumped;
    pii _move;
    int _max_tacos = 0;
    stack<tuple<int, bool, pii>> s; // stores _tacos, (i, j)
    s.emplace(0, false, start);
    while(!s.empty()) {
        tie(_tacos, _jumped, _move) = s.top(); s.pop();
        tie(i, j) = _move;
        if(_visited[i][j]) continue;
        _visited[i][j] = true;
        if(!visited[i][j] && board[i][j] == 'T') _tacos += 1;
        if(_tacos > _max_tacos) _max_tacos = _tacos;
        if(DEBUG)
            printf("here %d, %d; board %c; jumped %d\n", i, j, board[i][j], _jumped);
        vector<pii> moves;
        if(i + 1 <  n) moves.emplace_back(i + 1, j);
        if(j + 1 <  m) moves.emplace_back(i, j + 1);
        if(i - 1 >= 0) moves.emplace_back(i - 1, j);
        if(j - 1 >= 0) moves.emplace_back(i, j - 1);
        for(pii move : moves) {
            tie(_i, _j) = move;
            if(board[i][j] == '#') {
                // currently on wall
                if(board[_i][_j] != '#' && !visited[_i][_j]) {
                    // drop to unseen space from first traversal
                    s.emplace(_tacos, true, move);
                }
            } else if(board[_i][_j] == '#') {
                // not on wall and hit wall
                if(!_jumped)
                    // if not used jump than use it on wall
                    s.emplace(_tacos, true, move);
            } else if(board[_i][_j] != '#') {
                // not on wall and hit open space
                s.emplace(_tacos, _jumped, move);
            }
        }
    }
    return tacos + _max_tacos;
}

int test() {
    int n; // rows
    int m; // columns
    int i, j, k;
    int u, v, x, y;
    cin >> n >> m;
    // converting strings to vector<vector<char>> breaks??
    vector<string> board(n); // mtx of board
    pii start;
    string row;
    for(i = 0; i < n; i++) {
        cin >> board[i];
        for(j = 0; j < m; j++) {
            if(board[i][j] == 'S')
                start = {i, j};
        }
    }

    return search(board, start, n, m);
}

/*
BFS, then DFS
g++ -std=c++11 h-mandalorian.cpp -o k
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }
    int i, T;
    cin >> T;
    vector<int> ans;
    ans.reserve(T);
    for(i = 0; i < T; i++) ans.push_back(test());
    for(int a : ans)
        cout << a << endl;

    return 0;
}

