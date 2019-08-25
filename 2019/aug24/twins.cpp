#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
g++ -std=c++11 -o k twins.cpp

4 
11 99 88 17 19 20 12 13 33 44
11 12 13 14 15 16 66 88 19 20
20 18 55 66 77 88 17 33 44 11
12 23 34 45 56 67 78 89 91 18
*/

int main() {
    bool z, m;
    int n;
    cin >> n;
    int a[n][10];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 10; j++)
            cin >> a[i][j];

    for(int i = 0; i < n; i++) {
        z = false; m = false;
        for(int j = 0; j < 10; j++) {
            cout << a[i][j] << (j == 9 ? "" : " ");
            if(a[i][j] == 17) z = true;
            if(a[i][j] == 18) m = true;
        }
        cout << endl;
        if(z && m) cout << "both" << endl;
        else if(z) cout << "zack" << endl;
        else if(m) cout << "mack" << endl;
        else cout << "none" << endl;
        cout << endl;
    }

    return 0;
}









