#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <array>
#include <utility>
using namespace std;

/*

g++ -std=c++11 e-exciting.cpp -o k
*/

void debug() {
    cout << "DEBUG" << endl;
}

int main() {
    int N, K, acc; acc = 0;
    cin >> N >> K;
    int a[N];

    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    sort(a, a+N);
    for(int j = N - 1; j > N - 1 - K; j--) {
        acc += a[j];
    }
    cout << acc << endl;

    return 0;
}

