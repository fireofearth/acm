#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;

int get_greatest(int i, vector<vector<int>> &v, int p, int pp) {
    if(p == pp) {
        int k1 = (p == 0 ? 1 : 0);
        int k2 = (p == 0 ? 2 : (p == 1 ? 2 : 1));
        return max(v[k1][i], v[k2][i]);
    } else {
        return max(v[0][i], max(v[1][i], v[2][i]));
    }
}

int get_index(int i, vector<vector<int>> &v, int p, int pp) {
    if(p == pp) {
        int k1 = (p == 0 ? 1 : 0);
        int k2 = (p == 0 ? 2 : (p == 1 ? 2 : 1));
        return (v[k1][i] > v[k2][i] ? k1 : k2);
    } else {
        return (v[0][i] > v[1][i] ? (v[2][i] > v[0][i] ? 2 : 0) : (v[2][i] > v[1][i] ? 2 : 1));
    }
}

/*
g++ -std=c++11 c-vacation.cpp -o k
does not work
*/
int main() {
    int N, a, b ,c;
    cin >> N;
    vector<vector<int>> v; // a[0] a ; a[1] b ; a[2] c
    v.push_back(vector<int>());
    v.push_back(vector<int>());
    v.push_back(vector<int>());
    for(int i = 0; i < N; i++) {
        cin >> a >> b >> c;
        v[0].push_back(a);
        v[1].push_back(b);
        v[2].push_back(c);
    }
    
    int h[N]; // amount of happiness
    int l[N]; // activity at day i
    h[0] = get_greatest(0, v, -2, -1);
    l[0] = get_index(1, v, -2, -1);
    if(N >= 2) {
        h[1] = h[0] + get_greatest(1, v, -2, -1);
        l[1] = get_index(1, v, -2, -1);
    }

    for(int i = 2; i < N; i++) {
        h[i] = h[i-1] + get_greatest(i, v, l[i-1], l[i-2]);
        l[i] = get_index(i, v, l[i-1], l[i-2]);
    }
    cout << h[N-1] << endl;

    return 0;
}
