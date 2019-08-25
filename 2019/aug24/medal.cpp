#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
g++ -std=c++11 -o k medal.cpp

5
10 5 15 10 1 0
10 5 15 10 6 10
12 5 10 5 20 30
10 0 15 10 5 30
10 5 15 10 5 15
*/

int main() {
    bool cnt, clr;
    int ucnt, rcnt;
    int n;
    cin >> n;
    int a[n][6]; // u_g u_s u_b r_g r_s r_b
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 6; j++)
            cin >> a[i][j];

    for(int i = 0; i < n; i++) {
        cnt = false;
        clr = false;

        // count
        ucnt = 0; rcnt = 0;
        for(int j = 0; j < 3; j++) {
            ucnt += a[i][j]; rcnt += a[i][3 + j];
        }
        if(ucnt > rcnt) cnt = true;

        // color
        if(a[i][0] > a[i][3])
            clr = true;
        else if(a[i][0] >= a[i][3]) {
            if(a[i][1] > a[i][4]) {
                clr = true;
            } else if(a[i][1] >= a[i][4]) {
                clr = (a[i][2] > a[i][5]);
            }
        }

        for(int j = 0; j < 6; j++) {
            cout << a[i][j] << (j == 5 ? "" : " ");
        }
        cout << endl;
        if(cnt && clr) cout << "both" << endl;
        else if(cnt) cout << "count" << endl;
        else if(clr) cout << "color" << endl;
        else cout << "none" << endl;
        cout << endl;
    }

    return 0;
}


