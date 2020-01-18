#include <bits/stdc++.h>
#include <iostream>
using namespace std;

/*
g++ -std=c++11 e-eggfruit.cpp -o k
Since cake.size() may be 10^5 a bruteforce approach does not work
*/
int main() {
    // cake contains E or P
    // slice should contain at least one E
    string cake;
    int s, ind, slice_sz, j, k;
    // pos last slice with eggplant
    int last_slice_pos;
    int counter = 0;
    bool has_eggplant;
    cin >> cake;
    cin >> s;
    for(slice_sz = 1; slice_sz <= s; slice_sz++) {
        // i is slice size. Should be bounded by s
        last_slice_pos = -1;
        for(j = 0; j < cake.size(); j++) {
            // j is the pos. of the cake slice starts at
            // this scope checks eggplant containment
            has_eggplant = false;
            for(k = 0; k < slice_sz; k++) {
                ind = (k + j) % cake.size();
                if(cake[ind] == 'E') {
                    has_eggplant = true;
                    break;
                }
            }
            if(has_eggplant)
                counter++;
        }
    }
    cout << counter << endl;
    return 0;
}
