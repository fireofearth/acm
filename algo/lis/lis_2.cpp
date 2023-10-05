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
A O(n log n) solution to Longest Increasing Subsequence (LIS).
Strictly increasing sequence

Made some mistaken modifications. Check this still works?

g++ -std=c++11 lis_2.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, j, k;
    int n;
    int l, w;
    cin >> n;
    vector<int> v(n);
    for(i = 0; i < n; i++) {
        cin >> v[i];
    }

    // for each iteration i
    // memo[j] smallest index k of v[k] such that v[0]..v[i] has
    // an increasing subsequence of length j ending at v[k]
    vector<int> memo(n + 1);
    memo[0] = -1;
    // for each iteration i
    // pred[k] preceding index k' longest increasing subsequence
    // in v[0]..v[i] ending at k so this sequence contains v[k'], v[k]
    vector<int> pred(n);
    int largest = 0; // longest subsequence found so far
    int lo, mid, hi, length;
    for(i = 0; i < n; i++) {
        lo = 1;
        hi = largest + 1;
        // use binary search to find index mid
        // such that v[memo[mid]] <= v[i]
        while(lo < hi) {
            mid = (lo + hi) / 2;
            if(v[memo[mid]] <= v[i])
                lo = mid + 1;
            else
                hi = mid;
        }
        length = lo;
        pred[i] = memo[length - 1];
        memo[length] = i;
        if(length > largest) largest = length;
    }

    cout << largest << endl;
    vector<int> seq(largest);
    k = memo[largest];
    for(i = largest - 1; i >= 0; i--) {
        seq[i] = v[k];
        k = pred[k];
    }
    printv(seq);
    return 0;
}
