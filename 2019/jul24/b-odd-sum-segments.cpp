#include <iostream>

using namespace std;

typedef unsigned long long int mlong;

/*
g++ -std=c++11 -o k b-odd-sum-segments.cpp

array a of n integers a1, ..., an
split into exactly k non-empty intersecting subsegments
    each subsegment has odd sum

each n of elts belong to exactly one of k subsegments

if # odds less than k then false
if # odds at least k then
    if k is odd want (# odds) odd
    if k is even want (# odds) even

4
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
14 2
2 4 3 1 1 4 0 1 0 2 4 3 2 1
13 2
2 4 3 1 1 4 0 1 0 2 4 3 2

7 3
(1) (1 1 1) (1 1 1)

8 4
(1) (1) (1 1 1) (1 1 1)

8 3
1 1 1 1 1 1 1 1

7 4
1 1 1 1 1 1 1 NO

1
9 3
2 4 3 1 2 4 0 1 0
o: 3 4 10
*/

void debug() {
    cout << "DEBUG" << endl;
}

bool isodd(mlong a) {
    return a % 2 == 1;
}

/**
 * timeout
 */

bool solve(mlong abg, mlong *a, mlong asz, mlong *r, mlong rsz) {
    if(rsz == 0) return true;
    mlong acc = 0; bool b;
    for(mlong i = abg; i <= asz; i++) {
        acc += a[i-1];
        if(isodd(acc) && (rsz == 1 ? i == asz : true)) {
            // invariant: asz >= rsz
            b = solve(i + 1, a, asz, r + 1, rsz - 1);
            if(b) {
                *r = i;
                return true;
            }
        }
    }
    return false;
}

int main() {
    mlong q; // num queries
    cin >> q;
    mlong n[q]; mlong k[q];
    mlong *a[q];
    mlong *r[q];
    bool b;

    for(mlong i = 0; i < q; i++) {
        cin >> n[i] >> k[i];
        a[i] = new mlong[n[i]];
        r[i] = new mlong[k[i]];
        for(mlong j = 0; j < n[i]; j++)
            cin >> a[i][j];
    }

    for(mlong i = 0; i < q; i++) {
        b = solve(1, a[i], n[i], r[i], k[i]);
        if(b) {
            cout << "YES" << endl;
            for(mlong j = 0; j < k[i]; j++)
                cout << r[i][j] << (j == k[i] - 1 ? "" : " ");
            cout << endl;
        } else
            cout << "NO" << endl;
    }

    return 0;
}
