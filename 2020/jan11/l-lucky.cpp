#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<lld>::max();

/*
g++ -std=c++11 l-lucky.cpp -o k
*/
int main() {
    freopen("lucky.in", "r", stdin);
    freopen("lucky.out", "w", stdout);

    int i, j, k, r, c;
    cin >> r >> c;
    int t[r][c];
    // [left, top, right, bottom]
    int m[r][c][4];
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            cin >> t[i][j];
        }
    }

    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            // left
            if(j == 0) m[i][j][0] = 0;
            else m[i][j][0] = max(m[i][j-1][0], t[i][j-1]);

            // top
            if(i == 0) m[i][j][1] = 0;
            else m[i][j][1] = max(m[i-1][j][1], t[i-1][j]);
        }
    }

    for(i = r - 1; i > -1; i--) {
        for(j = c - 1; j > -1; j--) {
            // right
            if(j == c - 1) m[i][j][2] = 0;
            else m[i][j][2] = max(m[i][j+1][2], t[i][j+1]);

            // bottom
            if(i == r - 1) m[i][j][3] = 0;
            else m[i][j][3] = max(m[i+1][j][3], t[i+1][j]);
        }
    }

    int count = 0;   
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            for(k = 0; k < 4; k++) {
                if(t[i][j] > m[i][j][k]) count++;
            }
        }
    }

    cout << count << endl;

    return 0;
}
