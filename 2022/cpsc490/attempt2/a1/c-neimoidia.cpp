#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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
g++ -std=c++17 -o k c-neimoidia.cpp

cat ../../a1/tests/c-neimoidia-1.{in,out}
./k < ../../a1/tests/c-neimoidia-1.in
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}

