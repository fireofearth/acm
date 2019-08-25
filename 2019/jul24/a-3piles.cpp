#include <iostream>

using namespace std;

typedef unsigned long long int mlong;

/*
g++ -std=c++11 -o k a-3piles3.cpp

1. alice takes 1 pile of 3
2. bob takes 1 pile of remaining 2
3. last pile split between alice and bob

if n1 >= n2 + n3 then alice takes n2, bob takes n3 and n1 is shared

There is a trivially easy solution: (n1 + n2 + n3) / 2

4
1 3 4
1 10 100
10000000000000000 10000000000000000 10000000000000000
23 34 45
*/

void debug() {
    cout << "DEBUG" << endl;
}

mlong max(mlong a, mlong b) {
    return a > b ? a : b;
}

mlong min(mlong a, mlong b) {
    return a > b ? b : a;
}

mlong abs(mlong a) {
    return a >= 0 ? a : -a;
}

// network sort
void sort_me(mlong &n1, mlong &n2, mlong &n3) {
    mlong m1, m2, m3;
    if(n1 >= n2 && n1 >= n3) {
        m1 = n1;
        m2 = max(n2, n3);
        m3 = min(n2, n3);
    } else if(n2 >= n1 && n2 >= n3) {
        m1 = n2;
        m2 = max(n1, n3);
        m3 = min(n1, n3);
    } else { // if(n3 >= n1 && n3 >= n2)
        m1 = n3;
        m2 = max(n1, n2);
        m3 = min(n1, n2);
    }
    n1 = m1; n2 = m2; n3 = m3;
}

mlong take(mlong n1, mlong n2, mlong n3) {
    mlong a, b, t, s;
    sort_me(n1, n2, n3);
    a = n2;
    b = n3;
    t = abs(a - b);
    if(t >= n1) return n1 + min(n2, n3);
    else // t < n2
        return max(n2, n3) + ((n1 - t) / 2);
}

int main() {
    int q; // num queries
    cin >> q;
    mlong n[q][3];
    for(int i = 0; i < q; i++) {
        cin >> n[i][0] >> n[i][1] >> n[i][2];
    }
    for(int i = 0; i < q; i++) {
        cout << take(n[i][0], n[i][1], n[i][2]) << endl;
    }
    return 0;
}
