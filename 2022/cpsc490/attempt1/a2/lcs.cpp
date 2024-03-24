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
Longest Increasing Subsequence (LCS) using DP
g++ -std=c++11 lcs.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, j, k;
    string s, t;
    cin >> s >> t;

    // Compute LCS using 2D DP
    int n = s.size();
    int m = t.size();
    // rows represent word s's characters
    // columns represent word t's characters
    vector<vector<int>> memo(n + 1, vector<int>(m + 1));
    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++) {
            //printf("%d %d \n", i, j);
            if(s[i - 1] == t[j - 1])
                memo[i][j] = 1 + memo[i - 1][j - 1];
            else
                memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
        }
    // length of LCS
    cout << memo[n][m] << endl;

    // Recover LCS
    i = n; j = m;
    string o;
    while(i > 0 && j > 0) {
        if(s[i - 1] == t[j - 1]) {
            o += s[i - 1];
            i--; j--;
        } else if(memo[i][j] == memo[i][j - 1])
            j--;
        else
            i--;
    }
    reverse(o.begin(), o.end());
    cout <<  o << endl;

    return 0;
}

