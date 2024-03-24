#include <bits/stdc++.h>
using namespace std;

double mean(vector<double> c) {
    double acc = 0;
    for(auto d : c) acc += d;
    acc /= c.size();
    return acc;
}

double _round2(double d) {
    return round(100*d) / 100;
}

/*
g++ -std=c++11 a-bagels.cpp -o k
*/
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, T;
    double b;
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


    for(i = 0; i < T; i++) {
        b = mean(a[i]);
        cout << setprecision(2) << fixed << _round2(b) << endl;
        // Testing
        //for(j = 0; j < n[i]; j++) {
        //    cout << setprecision(2) << fixed << a[i][j] << " ";
        //}
        //cout << endl;
    }

    return 0;
}

