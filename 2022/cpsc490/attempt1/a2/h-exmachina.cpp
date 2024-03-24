#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool DEBUG = false;

/*
2D DP of divide and conquer
g++ -std=c++11 h-exmachina.cpp -o k

4
2 2
2 100
100 2
2 2

out:
416

6
2 100
100 2
2 4
4 8
8 16
16 2

4
2 2
2 2
2 100
100 2

5
81 38
38 81
81 35
35 84
84 10

*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    int i, j;
    int N;
    int n, m;

    cin >> N; // pile size
    vector<array<ll, 2>> mat(N);
    for(i = 0; i < N; i++) {
        // matrix dimensions
        cin >> n >> m;
        mat[i] = {n, m};
    }

    ll ops, _ops;
    vector<vector<ll>> memo(N, vector<ll>(N+1));
    for(i = 0; i < N - 1; i++) {
        // multiply 2 consecutive matrices
        memo[i][2] = mat[i][0]*mat[i+1][0]*mat[i+1][1];
        if(DEBUG) printf("n=2, i=%d, ops=%lld \n", i, memo[i][2]);
    }
    for(n = 3; n <= N; n++) {
        for(i = 0; i <= N - n; i++) {
            // subarray of n matrices to multiply
            ops = numeric_limits<ll>::max();
            for(m = 1; m < n; m++) {
                // M(x,y)*M(y,z) has x*y*z operations
                _ops = mat[i][0] * mat[i+m][0] * mat[i+n-1][1];
                _ops += memo[i][m];
                _ops += memo[i+m][n-m];
                ops = min(ops, _ops);
            }
            memo[i][n] = ops;
            if(DEBUG) printf("n=%d, i=%d, ops=%lld \n", n, i, ops);
        }
    }

    cout << memo[0][N] << endl;

    return 0;
}

