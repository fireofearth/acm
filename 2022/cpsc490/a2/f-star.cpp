#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool DEBUG = false;

ll MODVAL = 1000000000 + 7;

vector<vector<ll>> CHOOSE(1001, vector<ll>(1001));

inline ll modmul(ll a, ll b) {
    return (a * b) % MODVAL;
}

inline ll modadd(ll a, ll b) {
    return (a + b) % MODVAL;
}

void precompute(vector<vector<ll>> &memo, int N, int K) {
    int i, j;
    int n, k;
    int min_nK;
    ll c, d;

    for(n = 1; n <= 1000; n++) {
        CHOOSE[n][0] = 1;
        for(k = 1; k < n; k++) {
            CHOOSE[n][k] = modadd(CHOOSE[n-1][k-1], CHOOSE[n-1][k]);
        }
        CHOOSE[n][n] = 1;
    }

    memo[1][0] = 1;
    memo[2][0] = 2;

    for(n = 3; n <= N; n++) {
        min_nK = min(n / 2, K);
        for(k = 0; k <= min_nK; k++) {
            // memoize f(n, k)
            c = 0;
            for(i = 1; i <= n - 2; i++) {
                for(j = 0; j <= k - 1; j++) {
                    d = modmul(
                        modmul(memo[i][j], CHOOSE[n - 1][i]),
                        memo[n - i - 1][k - 1 - j]
                    );
                    c = modadd(c, d);
                }
            }
            // edge subproblems
            c = modadd(c, modmul(2, memo[n - 1][k]));
            memo[n][k] = c;
        }
    }
}

/*
2D DP of divide and conquer
g++ -std=c++11 f-star.cpp -o k

6
4 0
4 1
3 1
10 2
6 2
7 3

8
16
2
1304832
272
272

*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    int i, j;
    int n, k;
    int T, N, K;

    cin >> T;
    int max_N = 0;
    int max_K = 0;
    vector<pair<int, int>> qs(T);
    for(i = 0; i < T; i++) {
        cin >> N >> K;
        qs[i] = {N, K};
        max_N = max(max_N, N);
        max_K = max(max_K, K);
    }
    vector<vector<ll>> memo(max_N + 1, vector<ll>(max_K + 1, 0));
    precompute(memo, max_N, max_K);

    for(pair<int, int> p : qs) {
        tie(N, K) = p;
        cout << memo[N][K] << endl;
    }   

    return 0;
}

