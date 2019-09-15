#include <iostream>
#include <unordered_map>
using namespace std;

typedef unsigned long long int mlong;

/*

g++ -std=c++11 toy-soldiers.cpp -o k
there are 10**9 colours

3
1 4 2
7
1 5
2 4
3 2
3 2
1 2
4 2
2 1
 */

int main() {

    int n; // number of soldiers
    cin >> n;
    int a[n]; // colors the soldiers painted
    // key - paint #
    // value - # soldiers painted with (paint #)
    unordered_map<int, int> paint_cnt;
    bool is_reached = false;
    int same_clr = 0;

    for(int i = 0; i < n; i++) {
        // set values
        cin >> a[i];
        a[i] -= 1;
        // << 0 >> check
        if(paint_cnt[ a[i] ]) { // colour count exists
            paint_cnt[ a[i] ] += 1;
        } else { // set new count
            paint_cnt[ a[i] ] = 1;
        }
        if(paint_cnt[ a[i] ] == n)
            is_reached = true;
    }

    int m; // number of times repainted soldiers
    cin >> m;
    int k[m]; // the soldier number k_i
    int x[m]; // the number of colour k_i has been painted 

    for(int i = 0; i < m; i++) {
        // set values
        cin >> k[i] >> x[i];
        k[i] -= 1; x[i] -= 1; // 0-index this

        // if new colour == original color then skip
        // since colour counts don't change
        if( a[ k[i] ] == x[i] ) {
            continue;
        } else { // must be defined
            paint_cnt[ a[ k[i] ] ] -= 1;
            a[ k[i] ] = x[i];
        }

        a[ k[i] ] = x[i];
        if(paint_cnt[ a[ k[i] ] ]) { // new color count exists
            paint_cnt[ a[ k[i] ] ] += 1;
        } else {
            paint_cnt[ a[ k[i] ] ] = 1;
        }
        if(!is_reached && paint_cnt[ a[ k[i] ] ] == n) {
            is_reached = true;
            same_clr = i + 1;
        }
    }
    
    if(is_reached)
        cout << same_clr << endl;
    else
        cout << -1 << endl;
    return 0;
}
