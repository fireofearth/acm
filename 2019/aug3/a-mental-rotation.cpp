#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long int mlong;

/*
g++ -std=c++11 -o k a-mental-rotation.cpp

1 <= N <= 1000; S =(L,R)+ up to 100 times
NxN array

3 R
>vv
.v.
^^<

3 L
>vv
.v.
<<v

3 R
>vv
.v.
<<v


3 L
>v.
^v.
...
 
4 R
>.>.
....
<.<.
....
*/


void debug() {
    cout << "DEBUG" << endl;
}

// (R, =>) ; (L, <=)
char arrs[4] = {'>', 'v', '<', '^'};

char cg(char c, bool b) {
    if(arrs[0] == c)
        return b ? arrs[1] : arrs[3];
    else if(arrs[1] == c)
        return b ? arrs[2] : arrs[0];
    else if(arrs[2] == c)
        return b ? arrs[3] : arrs[1];
    else if(arrs[3] == c)
        return b ? arrs[0] : arrs[2];
    else return c;
}

void rotRight(char **map, int n) {
    char temp1, temp2; int ii, jj;
    for(int i = 0; i < n / 2; i++) {
        for(int j = 0; j < n / 2 + (n % 2 == 0 ? 0 : 1); j++) {
            //ii = i; jj = j;
            //temp2 = map[i][j];
            //for(int k = 0; k < 3; k++) {
            //    ii = jj; jj = n - ii - 1;
            //    temp1 = map[ii][jj];
            //    map[ii][jj] = cg(temp2, true);
            //    temp2 = temp1;
            //}
            temp1 = map[j][n - i - 1];
            map[j][n - i - 1] = cg(map[i][j], true);
            temp2 = temp1;
            temp1 = map[n - i - 1][n - j - 1];
            map[n - i - 1][n - j - 1] = cg(temp2, true);
            temp2 = temp1;
            temp1 = map[n - j - 1][i];
            map[n - j - 1][i] = cg(temp2, true);
            map[i][j] = cg(temp1, true);
        }
    }
    if(n % 2 == 1)
        map[n / 2][n / 2] = cg(map[n / 2][n / 2], true);
}

void rotLeft(char **map, int n) {
    char temp1, temp2; int ind1, ind2;
    for(int i = 0; i < n / 2; i++) {
        for(int j = 0; j < n / 2 + (n % 2 == 0 ? 0 : 1); j++) {
            temp1 = map[n - j - 1][i];
            map[n - j - 1][i] = cg(map[i][j], false);
            temp2 = temp1;
            temp1 = map[n - i - 1][n - j - 1];
            map[n - i - 1][n - j - 1] = cg(temp2, false);
            temp2 = temp1;
            temp1 = map[j][n - i - 1];
            map[j][n - i - 1] = cg(temp2, false);
            map[i][j] = cg(temp1, false);

        }
    }
    if(n % 2 == 1)
        map[n / 2][n / 2] = cg(map[n / 2][n / 2], false);
}

int main() {
    int n; string rots;
    cin >> n;
    cin >> rots;
    char *map[n];
    for(int i = 0; i < n; i++) {
        map[i] = new char[n];
        cin >> map[i];
    }

    for(int i = 0; i < rots.length(); i++) {
        if(rots[i] == 'R')
            rotRight(map, n);
        else
            rotLeft(map, n);
    }

    for(int i = 0; i < n; i++)
        cout << map[i] << endl;

    return 0;
}
