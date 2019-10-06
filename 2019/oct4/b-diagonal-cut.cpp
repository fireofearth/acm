#include<iostream>
#include<numeric>
using namespace std;

typedef unsigned long long int mlong;


/**
g++ -std=c++17 b-diagonal-cut.cpp -o k
1 <= M, N <= 10^18 leads to issues. Need adjustment
*/

int main() {
    mlong M, N;
    cin >> M >> N;
    mlong g = gcd(M, N);
    mlong m = M / g;
    mlong n = N / g;
    mlong b;
    if(m == n) {
        b = n;
    } else if(m % 2 == n % 2) {
        b = 1;
    }
    mlong f = b * g;
    printf("%llu", f);
    cout << endl;
    return 0;
}
