#include <bits/stdc++.h>
using namespace std;

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

/*
A O(n^2) solution to Longest Increasing Subsequence (LIS).
Monotonically increasing sequence

trivial cases works

in:
5
2 1 9 3 5

out:
3
1 3 5

in:
8
5 1 3 2 6 8 7 4

out:
4
1 3 6 8

in:
10
0 1 3 5 7 1 2 4 6 8

out:
7
0 1 1 2 4 6 8

in:
8
1 3 1 3 1 3 1 3

out:
5
1 3 3 3 3

g++ -std=c++11 lis_1.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, j, k;
    int n;
    cin >> n;
    vector<int> v(n);
    for(i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<int> memo(n);
    vector<int> pred(n);
    int largest = 1;
    int idx_largest = n - 1;
    for(i = n - 1; 0 <= i; i--) {
        memo[i] = 1;
        pred[i] = -1;
        for(j = i + 1; j < n; j++) {
            if(v[i] <= v[j]) {
                if(memo[i] < 1 + memo[j]) {
                    memo[i] = 1 + memo[j];
                    pred[i] = j;
                }
            }
        }
        if(memo[i] > largest) {
            largest = memo[i];
            idx_largest = i;
        }
    }
    cout << memo[idx_largest] << endl;
    //printv(memo);

    vector<int> seq;
    seq.reserve(largest);
    k = idx_largest;
    for(i = 0; i < largest; i++) {
        seq.push_back(v[k]);
        k = pred[k];

    }
    printv(seq);

    return 0;
}
