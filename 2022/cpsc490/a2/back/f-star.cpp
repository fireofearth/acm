#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool DEBUG = false;

ll MODVAL = 1000000000 + 7;

//vector<ll> FACTORIAL(1001);
vector<vector<ll>> CHOOSE(1001, vector<ll>(1001));

inline ll modmul(ll a, ll b) {
    return (a * b) % MODVAL;
}

inline ll modadd(ll a, ll b) {
    return (a + b) % MODVAL;
}

/*
2D DP of divide and conquer
g++ -std=c++11 f-star.cpp -o k

This works! Creating another clean version for submission.
*/
void main(int argc, char *argv[]) {

    int i, j;
    int n, k;
    int N, K;
    int min_nK;
    ll c, d;

    //FACTORIAL[0] = 1;
    //for(n = 1; n <= 1000; n++)
    //    FACTORIAL[n] = (FACTORIAL[n - 1] * n) % MODVAL;

    for(n = 1; n <= 1000; n++) {
        CHOOSE[n][0] = 1;
        for(k = 1; k < n; k++) {
            CHOOSE[n][k] = modadd(CHOOSE[n-1][k-1], CHOOSE[n-1][k]);
        }
        CHOOSE[n][n] = 1;

    }

    cin >> N >> K;
    vector<vector<ll>> memo(N + 1, vector<ll>(K + 1, 0));

    memo[1][0] = 1;
    memo[2][0] = 2;

    for(n = 3; n <= N; n++) {
        min_nK = min(n / 2, K);
        for(k = 0; k <= min_nK; k++) {
            // memoize f(n, k)
            c = 0;
            if(DEBUG) printf("(n=%d, k=%d) \n", n, k);
            for(i = 1; i <= n - 2; i++) {
                for(j = 0; j <= k - 1; j++) {
                    if(DEBUG) printf("    f(%d, %d) = %lld = f(i, j)  \n", i, j, memo[i][j]);
                    if(DEBUG) printf("    f(%d, %d) = %lld = f(n-i-1, k-1-j) \n", n - i - 1, k - 1 - j, memo[n - i - 1][k - 1 - j]);
                    if(DEBUG) printf("    choose(%d, %d) = %lld = choose(n-1, i) \n", n-1, i, CHOOSE[n - 1][i]);
                    d = modmul(
                        modmul(memo[i][j], CHOOSE[n - 1][i]),
                        memo[n - i - 1][k - 1 - j]
                    );
                    if(DEBUG) printf("    sum = %lld \n", d);
                    c = modadd(c, d);
                }
            }
            // edge subproblems
            if(DEBUG) printf("f(%d, %d) = %lld = f(n-1, k) \n", n-1, k, memo[n - 1][k]);
            c = modadd(c, modmul(2, memo[n - 1][k]));
            memo[n][k] = c;
            if(DEBUG) printf("f(n=%d, k=%d)=%lld \n", n, k, memo[n][k]);
        }
    }

    cout << memo[N][K] << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    int i, j;
    int n, k;
    int N, K;
    int min_nK;
    ll c, d;

    //FACTORIAL[0] = 1;
    //for(n = 1; n <= 1000; n++)
    //    FACTORIAL[n] = (FACTORIAL[n - 1] * n) % MODVAL;

    for(n = 1; n <= 1000; n++) {
        CHOOSE[n][0] = 1;
        for(k = 1; k < n; k++) {
            CHOOSE[n][k] = modadd(CHOOSE[n-1][k-1], CHOOSE[n-1][k]);
        }
        CHOOSE[n][n] = 1;

    }
    
    return 0;
}

