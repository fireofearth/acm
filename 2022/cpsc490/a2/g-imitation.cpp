#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool DEBUG = false;

/*
2D DP of divide and conquer
g++ -std=c++11 g-imitation.cpp -o k

in:
10
10 8 6 4 2 1 3 5 7 9

out:
30 25
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    int i, j;
    int n, k;
    int l, r;
    int N;

    cin >> N; // pile size
    vector<ll> pile(N);
    for(i = 0; i < N; i++) {
        cin >> pile[i]; // count of each cell in pile
    }
    array<vector<vector<ll>>, 2> memo;
    // memo[k][i][n] -> sub pile starting at index i, size n
    // k == 0 -> reward for player who moves first
    // k == 1 -> reward for player who moves second
    memo.fill(vector<vector<ll>>(N, vector<ll>(N + 1)));
    for(i = 0; i < N; i++) {
        memo[0][i][1] = pile[i];
        memo[1][i][1] = 0;
    }

    for(n = 2; n <= N; n++) {
        // n - size of sub-pile
        for(i = 0; i <= N - n; i++) {
            // i - starting index
            l = pile[i] + memo[1][i+1][n-1]; // take from left
            r = memo[1][i][n-1] + pile[i+n-1]; // take from right
            if(l > r) {
                // if taking left from pile is the more optimal
                // choice for player moving first
                memo[0][i][n] = l;
                memo[1][i][n] = memo[0][i+1][n-1];
            } else {
                // if taking right from pile is the more optimal
                // choice for player moving first
                memo[0][i][n] = r;
                memo[1][i][n] = memo[0][i][n-1];
            }
            if(DEBUG) printf("n=%d, i=%d; p1=%lld, p2=%lld\n",
                    n, i, memo[0][i][n], memo[1][i][n]);
        }
    }

    // output (first mover score) (second mover score)
    cout << memo[0][0][N] << " " << memo[1][0][N] << endl;

    return 0;
}

