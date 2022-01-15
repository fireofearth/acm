#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int search(
    vector<vector<int>> state,
    vector<array<pii, 2>> moves,
    int n, int m, int tar
) {
    vector<vector<int>> next_state;
    vector<array<pii, 2>> next_moves;
    int step;
    int val;
    int i, j, _i, _j, k, l, a, b;
    queue<
        tuple<
            int, // number of steps taken
            vector<vector<int>>, // board state
            vector<array<pii, 2>> // moves left to take
        >
    > q;
    q.emplace(0, state, moves);
    while(!q.empty()) {
        tie(step, state, moves) = q.front(); q.pop();

        // for each possible move
        for(k = 0; k < moves.size(); k++) {

            // pick a move on the board
            array<pii, 2> move_pair = moves[k];

            // get value of cells
            tie(i, j) = move_pair[0];
            tie(_i, _j) = move_pair[1];
            a = state[i][j];
            b = state[_i][_j];
            val = min(a*b, tar + 1);
            // return steps if found value
            if(val == tar) return step + 1;
            // skip steps if useless value
            if(val == 0) continue;
            if(val > tar) continue;

            // update possible moves
            next_moves = vector<array<pii, 2>>();
            for(l = 0; l < moves.size(); l++) {
                if(l != k) next_moves.emplace_back(moves[l]);
            }

            // for each move direction, add updated state to queue
            for(l = 0; l < 2; l++) {
                tie(i, j) = move_pair[l];
                tie(_i, _j) = move_pair[(l + 1) % 2];
                a = state[i][j];
                b = state[_i][_j];
                next_state = vector<vector<int>>(state);
                next_state[i][j] = 0; // set a
                next_state[_i][_j] = val; // set b
                q.emplace(step + 1, next_state, next_moves);
            }
        }
    }

    return -1;
}

/*
BFS on game state
g++ -std=c++11 e-twin.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; // rows
    int m; // columns
    int v; // target
    cin >> n >> m >> v;

    int i, j, k;
    int a, b, steps;
    bool trivial_y1 = false;
    bool trivial_y2 = false;
    bool trivial_n = false;
    trivial_y2 = (v == 0 && n*m > 1);
    trivial_n = (v == 0 && n*m == 1);

    // Initialize board
    vector<vector<int>> board(n, vector<int>(m)); // adj-mtx
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++) {
            cin >> a;
            board[i][j] = a;
            if(a == v) trivial_y1 = true;
        }
    
    // Return trivial case
    if(trivial_y1 == true) {
        cout << 0 << endl;
        return 0;
    }
    if(trivial_y2 == true) {
        cout << 1 << endl;
        return 0;
    }
    if(trivial_n == true) {
        cout << -1 << endl;
        return 0;
    }

    // Solve using BFS on moves
    vector<array<pii, 2>> moves;
    array<pii, 2> move_pair;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++) {
            // up-down
            if(i + 1 < n) {
                move_pair = {pii(i, j), pii(i + 1, j)};
                moves.push_back(move_pair);
            }
            // left-right
            if(j + 1 < m) {
                move_pair = {pii(i, j), pii(i, j + 1)};
                moves.push_back(move_pair);
            }
        }
    steps = search(board, moves, n, m, v);
    cout << steps << endl;

    return 0;
}

