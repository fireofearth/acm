#include<iostream>
#include<string>
#include<cmath>
using namespace std;

typedef long long int mlong;
typedef long double mdouble;

/**
g++ -std=c++11 c-gerrymandering.cpp -o k
*/

int main() {
    int P, D, d;
    mlong a, b;
    cin >> P >> D;
    mlong vA[D];
    mlong vB[D];
    mlong wA;
    mlong wB;
    mlong wdiff = 0;
    mlong vtotal = 0;
    bool Awins;
    
    for(int i = 0; i < D; i++) {
        vA[i] = 0;
        vB[i] = 0;
    }

    for(int i = 0; i < P; i++) {
        cin >> d >> a >> b;
        vA[d - 1] += a;
        vB[d - 1] += b;
        vtotal += a + b;
    }

//    for(int i = 0; i < D; i++) {
//        printf("%d %d\n", vA[i], vB[i]);
//    }

    for(int i = 0; i < D; i++) {
        if(vA[i] > vB[i]) { // A wins
            Awins = true;
            wB = vB[i];
            wA = vA[i] - ((mlong) floor(((mdouble) vA[i] + vB[i]) / 2.0)) - 1;
        } else { // B wins
            Awins = false;
            wA = vA[i];
            wB = vB[i] - ((mlong) floor(((mdouble) vA[i] + vB[i]) / 2.0)) - 1;
        }
        wdiff += (wA - wB);
        cout << (Awins ? "A" : "B") << " " << wA << " " << wB << endl;
    }
    cout.precision(8);
    cout << abs((mdouble) wdiff) / ((mdouble) vtotal) << endl;

    return 0;
}




