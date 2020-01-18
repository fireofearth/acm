#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;
lli MAX = numeric_limits<lli>::max();
lli MOD = 1000000007;

/*
Finding the longest path by doing topological sort
and do DP on each node in the list: the length of the
longest path that ends at the node in the list.

g++ -std=c++11 h-grid.cpp -o k
*/
int main() {
    int i, j;
    int H, W;
    cin >> H >> W;
    string b[H];
    lli m[H][W];
    for(i = 0; i < H; i++)
        cin >> b[i];
    
    // DP from smallest top left corner
    for(i = 0; i < H; i++) {
        for(j = 0; j < W; j++) {
            if(i == 0 && j == 0) m[i][j] = 1;
            else if(b[i][j] == '#') m[i][j] = -1;
            else {
                m[i][j] = 0;
                if(i > 0 && m[i-1][j] > -1)
                    m[i][j] += m[i-1][j];
                if(j > 0 && m[i][j-1] > -1)
                    m[i][j] += m[i][j-1];
                m[i][j] %= MOD;
            }
        }
    }

    cout << m[H-1][W-1] << endl;

    return 0;
}
