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

/*
Knapsack using DP
g++ -std=c++11 knapsack.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, j, k;
    int n; // items
    int W; // capacity
    cin >> n >> W;
    vector<int> weight(n);
    vector<ll> value(n);
    for(i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    // Compute Knapsack using 2D DP
    // rows represent capacity of subproblem
    // columns represent number of items of subproblem
    vector<vector<ll>> memo(W + 1, vector<ll>(n + 1));
    for(i = 1; i <= W; i++)
        for(j = 1; j <= n; j++) {
            if(weight[j - 1] <= i)
                // if remaining capacity i - weight[j - 1] is non-negative
                // consider choosing item j - 1
                memo[i][j] = max(
                    memo[i - weight[j - 1]][j - 1] + value[j - 1],
                    memo[i][j - 1]
                );
            else
                memo[i][j] = memo[i][j - 1];
            //printf("(%d, %d); %lld \n", i, j, memo[i][j]);
        }
    // total value in knapsack
    cout << memo[W][n] << endl;

    // Recover knapsack
    i = W; j = n;
    vector<int> o;
    while(i > 0 && j > 0) {
        if(memo[i][j] != memo[i][j - 1]) {
            o.push_back(j - 1);
            i -= weight[j - 1];
        }
        j--;
    }
    reverse(o.begin(), o.end());
    for(int i : o) {
        cout << weight[i] << " " << value[i] << endl;
    }

    return 0;
}

