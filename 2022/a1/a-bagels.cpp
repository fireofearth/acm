#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

double _mean(vector<ll> c, int n) {
    ll acc = 0;
    for(ll d : c) acc += d;
    double num = static_cast<double>(acc);
    double div = static_cast<double>(n);
    return num / div;
}

/*
Floats must be converted to integrals when doing sum operation.
Conversion should use static_cast<T>(f)
<https://stackoverflow.com/questions/2544394/c-floating-point-to-integer-type-conversions>
g++ -std=c++11 a-bagels.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, T;
    double b; // stores 0.00 ... 100.99
    cin >> T; // 10^3

    vector<int> n(T); // 10^2
    vector<vector<double>> a(T); // 0.00 ... 100.99

    for(i = 0; i < T; i++) {
        cin >> n[i];
        a[i] = vector<double>(n[i]);
        for(j = 0; j < n[i]; j++) {
            cin >> a[i][j];
        }
    }

    double h = 100.;
    vector<vector<ll>> c(T); // 0 ... 10099
    for(i = 0; i < T; i++) {
        c[i] = vector<ll>(n[i]);
        for(j = 0; j < n[i]; j++) {
            c[i][j] = static_cast<ll>(round(h*a[i][j]));
        }
    }

    for(i = 0; i < T; i++) {
        b = round(_mean(c[i], n[i])) / h;
        cout << setprecision(2) << fixed << b << endl;
        // Testing
        //for(j = 0; j < n[i]; j++) {
        //    cout << setprecision(2) << fixed << a[i][j] << " ";
        //}
        //cout << endl;
    }

    return 0;
}

