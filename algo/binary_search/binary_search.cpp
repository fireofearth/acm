#include<bits/stdc++.h>
using namespace std;

/*
g++ -std=c++11 binary_search.cpp -o k

8
1 5
5
1 5
0
2 5
1 5
2 5
5 1
2 5
1 6
2 5
6 1
5 5
1 5 6 10 11
5 5
0 2 4 5 11

*/

/**
 * Binary search to find index of value in subarray of sorted array.
 * @param v The non-empty array to search values for.
 * @param beg The start index of subarray
 * @param end The ending index of subarray
 * @param a The value to find array
 * @returns The index of value in subarray or -1 if value does not exist
 */
int binary_search(const vector<int> &v, int beg, int end, int a) {
    int mid = (end + beg) / 2;
    while(beg <= end) {
        mid = (end + beg) / 2;
        if(v[mid] == a) break;
        else if(v[mid] < a) beg = mid + 1;
        else end = mid - 1;
    }
    if(v[mid] == a) return mid;
    else return -1;
}

int test() {
    int n, a;
    cin >> n;
    cin >> a;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    int beg = 0;
    int end = n - 1;
    return binary_search(v, beg, end, a);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    vector<int> ans(T);
    for(int i = 0; i < T; i++) ans[i] = test();
    for(int i = 0; i < T; i++) cout << ans[i] << endl;
    return 0;
}
