#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;

/*
g++ -std=c++11 b-frog.cpp -o k
*/
int main() {
    int N, K;
    cin >> N >> K;
    int h[N];
    for(int i = 0; i < N; i++) {
        cin >> h[i];
    }
    
    int c[N];
    c[0] = 0;
    for(int i = 1; i < N; i++) {
        c[i] = -1;
        for(int j = i-1; j >= max(0, i-K); j--) {
            if(c[i] == -1)
                c[i] = abs(h[i] - h[j]) + c[j];
            else
                c[i] = min(c[i], abs(h[i] - h[j]) + c[j]);
        }
    }
    cout << c[N-1] << endl;

    return 0;
}
