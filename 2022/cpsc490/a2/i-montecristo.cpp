#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool DEBUG = false;

void printv(vector<pii> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << "(" << v[i].first << "," << v[i].second << ")";
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

bool comp(const pii &a, const pii &b) {
    if(a.second == b.second)
        return a.first > b.first;
    return a.second < b.second;
    //if(a.first == b.first)
    //    return a.second < b.second;
    //return a.first < b.first;
}

int lis() {
    int i, j, k;
    int l, w, h;
    int n;
    cin >> n;
    vector<pii> v(n);
    for(i = 0; i < n; i++) {
        cin >> l >> w >> h;
        v[i] = {l, w};
    }
    sort(v.begin(), v.end(), comp);
    printv(v);

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
        // such that v[memo[mid]] < v[i]
        while(lo < hi) {
            mid = (lo + hi) / 2;
            if(v[memo[mid]] < v[i])
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
    vector<pii> seq(largest);
    k = memo[largest];
    for(i = largest - 1; i >= 0; i--) {
        seq[i] = v[k];
        k = pred[k];
    }
    reverse(seq.begin(), seq.end());
    printv(seq);
    return largest;
}

int solve() {
    int i, j, k;
    int l, w, h;
    int n;
    cin >> n;
    vector<pii> v(n);
    for(i = 0; i < n; i++) {
        cin >> l >> w >> h;
        v[i] = {l, w};
    }
    sort(v.begin(), v.end());


}

/*
1D DP of divide and conquer
g++ -std=c++11 i-montecristo.cpp -o k

trivial cases work
edge case

3
2 4 1
1 2 3
4 5 2

4
2 4 1
1 2 1
2 1 1
4 5 1

5
2 2 1
1 1 1
1 2 1
3 2 1
3 3 1

*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }

    lis();
    return 0;
}

