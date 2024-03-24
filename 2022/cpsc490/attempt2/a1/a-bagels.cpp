#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

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
2
1 1.00
8 96.01 75.73 54.88 49.12 44.20 76.87 45.32 14.00

g++ -std=c++17 a-bagels.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j;
    int T;
    int n;
    vector<double> o(T, 0.);
    double c;

    cin >> T;

    for (i = 0; i < T; i++) {
        cin >> n;
        for (j = 0; j < n; j++) {
            cin >> c;
            o[i] += c;
        }
        o[i] /= n;
        o[i] = round(100. * o[i]) / 100.;
    }

    for (i = 0; i < T; i++) {
        cout << setprecision(2) << fixed << o[i] << endl;
    }

    return 0;
}

