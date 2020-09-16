#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
g++ -std=c++11 g-fibonacci.cpp -o k
failed...
*/
int main() {
    vector<ll> F;
    F.push_back(1); // F0
    F.push_back(1); // F1
    unordered_set<int> s;
    map<int, int> m;
    int i, n, Q;
    cin >> Q;
    int K[Q];
    for(i = 0; i < Q; i++) {
        cin >> K[i];
    }
    for(i = 0; i < Q; i++) {
        s = unordered_set<int>();
        m = map<int, int>();
        n = 2;
        while(true) {
            if(n >= F.size())
                F.push_back(F[n-1] + F[n-2]);
            if(s.count((int) (F[n] % (ll) K[i])) > 0) {
                cout << m[(int) (F[n] % (ll) K[i])] << endl;
                break;
            }
            s.insert((int) (F[n] % (ll) K[i]));
            m[(int) (F[n] % (ll) K[i])] = n; 
            n++;
        }
    }
    for(ll i: F) cout << i << " ";
    return 0;
}

