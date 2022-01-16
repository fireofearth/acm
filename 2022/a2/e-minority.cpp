#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

bool DEBUG = false;

map<int, int> i_to_config = {
    {0,  1 + (2 << 2) + (3 << 4)}, // 1 2 3
    {1,  1 + (3 << 2) + (2 << 4)}, // 1 3 2
    {2,  2 + (1 << 2) + (3 << 4)}, // 2 1 3
    {3,  2 + (3 << 2) + (1 << 4)}, // 2 3 1
    {4,  3 + (1 << 2) + (2 << 4)}, // 3 1 2
    {5,  3 + (2 << 2) + (1 << 4)}, // 3 2 1
                      
    {6,  1 + (2 << 2) + (1 << 4)}, // 1 2 1
    {7,  2 + (1 << 2) + (2 << 4)}, // 2 1 2
    {8,  1 + (3 << 2) + (1 << 4)}, // 1 3 1
    {9,  3 + (1 << 2) + (3 << 4)}, // 3 1 3
    {10, 2 + (3 << 2) + (2 << 4)}, // 2 3 2
    {11, 3 + (2 << 2) + (3 << 4)}  // 3 2 3 
};

map<int, int> config_to_i = {
    {1 + (2 << 2) + (3 << 4), 0},
    {1 + (3 << 2) + (2 << 4), 1},
    {2 + (1 << 2) + (3 << 4), 2},
    {2 + (3 << 2) + (1 << 4), 3},
    {3 + (1 << 2) + (2 << 4), 4},
    {3 + (2 << 2) + (1 << 4), 5},

    {1 + (2 << 2) + (1 << 4), 6},
    {2 + (1 << 2) + (2 << 4), 7},
    {1 + (3 << 2) + (1 << 4), 8},
    {3 + (1 << 2) + (3 << 4), 9},
    {2 + (3 << 2) + (2 << 4), 10},
    {3 + (2 << 2) + (3 << 4), 11}
};

vector<int> get_prev_configs(int i) {
    // a b c <--> a + (b << 2) + (c << 4)
    int j = i_to_config[i];
    int a = j & 3;
    int b = (j >> 2) & 3;
    int c = (j >> 4) & 3;
    if(DEBUG) printf("a=%d b=%d c=%d \n", a, b, c);
    if(a == c) {
        if(a + b == 4)
            // {a, b} == {1, 3}
            c = 2;
        else if(a + b == 5)
            // {a, b} == {2, 3}
            c = 1;
        else
            // {a, b} == {1, 2}
            c = 3;
        int c1 = b + (a << 2) + (c << 4); // b a c
        int c2 = c + (a << 2) + (b << 4); // c a b
        int c3 = b + (a << 2) + (b << 4); // b a b
        int c4 = c + (a << 2) + (c << 4); // c a c
        int c5 = b + (c << 2) + (b << 4); // b c b
        vector<int> configs = {
            config_to_i[c1],
            config_to_i[c2],
            config_to_i[c3],
            config_to_i[c4],
            config_to_i[c5]
        };
        return configs;
    } else {
        int c1 = b + (a << 2) + (b << 4); // b a b
        int c2 = b + (c << 2) + (a << 4); // b c a
        int c3 = c + (a << 2) + (b << 4); // c a b
        int c4 = b + (c << 2) + (b << 4); // b c b
        vector<int> configs = {
            config_to_i[c1],
            config_to_i[c2],
            config_to_i[c3],
            config_to_i[c4]
        };
        return configs;
    }
}

ll MODVAL = 1000000000 + 7; //10^9 + 7

/*
DP with bits
g++ -std=c++11 e-minority.cpp -o k

1 <= N <= 10^18

*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    int n;
    int i, j, k;
    int b;
    int mask, key1, key2;
    vector<int> configs;
    ll d;
    cin >> n;
    vector<vector<ll>> memo(2, vector<ll>(12));
    // i = 1
    for(j = 0; j < 12; j++) {
        // configuration of grid's first column
        memo[0][j] = 1;
    }
    b = 0;
    for(i = 2; i <= n; i++) {
        // length i of subgrid
        b = b ^ 1;
        for(j = 0; j < 12; j++) {
            // configuration j of subgrid's last column
            if(DEBUG) cout << i << ": " << b << ": " << j << " " << bitset<8>(i_to_config[j]) << endl;
            configs = get_prev_configs(j);
            d = 0;
            for(k = 0; k < configs.size(); k++) {
                // configuration configs[k] of subgrid's second last column
                d = (d + memo[b ^ 1][configs[k]]) % MODVAL;
            }
            memo[b][j] = d;
            if(DEBUG) printf("memo %lld \n", memo[b][j]);
        }
    }
    d = 0;
    for(j = 0; j < 12; j++) {
        // configuration of grid's last column
        d = (d + memo[b][j]) % MODVAL;
    }
    cout << d << endl;

    return 0;
}

