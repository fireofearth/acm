#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;

/*
g++ -std=c++11 a-frog.cpp -o k
*/
int main() {
    int N;
    cin >> N;
    int h[N];
    for(int i = 0; i < N; i++) {
        cin >> h[i];
    }
    
    int c[N];
    c[0] = 0;
    if(N >= 2)
        c[1] = abs(h[1] - h[0]);
    for(int i = 2; i < N; i++) {
        c[i] = min(
                abs(h[i] - h[i-1]) + c[i-1],
                abs(h[i] - h[i-2]) + c[i-2]
        );
    }
    cout << c[N-1] << endl;

    return 0;
}
