#include <iostream>
using namespace std;

/*
g++ -std=c++11 k-kernel.cpp -o k
1 to 2*10^5 strings

gcd(a+b, b) = gcd(a, b)
implies that we only care about consecutive pairs of fibs
*/

int main() {

    int c, n, t1, t2;
    cin >> c;
    int a[c];
    for(int i = 0; i < c; i++) {
        cin >> n;
        n += 1;
        if(n > 3) {
            a[i] = 1 + (2 * (((n - (n % 3)) - 3) / 3)) + (n % 3);
        } else {
            a[i] = 0;
        }
    }

    for(int i = 0; i < c; i++)
        cout << a[i] << endl;

    return 0;
}

