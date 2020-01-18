#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long int lld;

/*
g++ -std=c++11 e-eggfruit.cpp -o k
I needed the lld type to make this pass,
since overflow affect the output
*/
int main() {
    // cake contains E or P
    // slice should contain at least one E
    string cake, cake_in;
    int s;
    // pos last slice with eggplant
    int dist;
    lld count = 0;
    cin >> cake_in;
    cin >> s;
    cake = cake_in + cake_in;
    int n = cake_in.size();
    int a[n*2];
    a[0] = -1;
    for(int i = 1; i < n * 2; i++) {
        if(cake[i - 1] == 'E')
            a[i] = i - 1;
        else
            a[i] = a[i - 1];

        if(i >= n) {
            if(a[i] == -1) {
                // only happens when no 'E' in cake
                break;
            }
            if(cake[i] == 'E') {
                dist = i - a[i];
                for(int j = 1; j <= min(dist, s); j++) {
                    count += (lld) j;
                }
                for(int j = dist + 1; j <= s; j++) {
                    count += (lld) dist;
                }
            }
        }
    }

    /*
    for(int i = 0; i < n * 2; i++) {
        cout << cake[i] << " " << a[i] << endl;
    }
    */

    cout << count << endl;
    return 0;
}
