#include <bits/stdc++.h>
using namespace std;

/*
g++ -std=c++11 i-coins.cpp -o k
*/
int main() {
    int i, j, N;
    cin >> N;
    float p[N];
    float m[N+1][N+1];
    for(i = 0; i < N; i++) {
        m[0][i] = 0.0;
        cin >> p[i];
    }
    m[0][0] = 1.0;
    m[0][N] = 0.0;
    for(i = 1; i <= N; i++) {
        // coin i is indexed i-1
        m[i][0] = m[i-1][0]*(1.0-p[i-1]);
        //cout << m[i][0] << " ";
        for(j = 1; j <= N; j++) {
            // j heads
            m[i][j] = m[i-1][j-1]*p[i-1] + m[i-1][j]*(1.0-p[i-1]);
            //cout << m[i][j] << " ";
        }
        //cout << endl;
    }
    float o = 0.0;
    for(i = N; i > N/2; i--) {
        o += m[N][i];
    }
    cout.precision(numeric_limits<float>::max_digits10);
    cout << o << endl;

    return 0;
}
