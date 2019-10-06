#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

typedef unsigned long long int mlong;

double pow2(double x) {
    return pow(x, 2.0);
}

double f(double x, double w, double g, double h) {
    return sqrt(pow2(g) + pow2(x)) + sqrt(pow2(h) + pow2(w - x));
}

double df(double x, double w, double g, double h) {
    return (x / sqrt(pow2(g) + pow2(x))) + ((x - w) / sqrt(pow2(h) + pow2(w - x)));
}

double bsearch(double w, double g, double h) {
    double left = 0;
    double right = w;
    double x, dfx;
    int i = 0;
    while(abs(left - right) > pow(10.0, -6) / 1.10) {
        //cout << "iter " << i << " " << abs(left - right) << endl;
        i++;
        if(i > 1000) break;
        x = (left + right) / 2;
        dfx = df(x, w, g, h);
        if(dfx == 0.0)
            break;
        else if(dfx < 0.0)
            left = x;
        else // (x > 0.0)
            right = x;
    }
    return f(x, w, g, h);
}

/**
g++ -std=c++17 m-zipline.cpp -o k
*/
double getmin(double w, double g, double h) {
    double x = abs(g - h);
    return sqrt(pow2(x) + pow2(w));
}

int main() {
    int n, w, g, h, r;
    cin >> n;
    double l[n];
    double L[n];

    for(int i = 0; i < n; i++) {
        cin >> w >> g >> h >> r;
        // compute minimum
        l[i] = getmin((double) w, (double) g, (double) h);
        g = g - r;
        h = h - r;
        // compute maximum
        L[i] = bsearch((double) w, (double) g, (double) h);
    }

    cout.precision(17);
    for(int i = 0; i < n; i++) {
        cout << l[i] << " " << L[i] << endl;
    }

    return 0;
}

