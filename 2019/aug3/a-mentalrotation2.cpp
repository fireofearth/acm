#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
g++ -std=c++11 -o k a-mentalrotation2.cpp

1 <= N <= 1000; S =(L,R)+ up to 100 times
NxN array

1 L
>

2 R
..
>>

3 RLLLLRLLLR
>vv
.v.
<<v

3 RLLLLRLLLLR
>vv
.v.
<<v
*/


void debug() {
    cout << "DEBUG" << endl;
}

// (R, =>) ; (L, <=)
char arrs[4] = {'>', 'v', '<', '^'};

inline void helper(vector<pair<char, int>> &v) {
    if(v.back().second % 4 == 0)
        v.pop_back();
    else {
        v.back().second = v.back().second % 4;
        if(v.back().second == 3) {
            v.back().second = 1;
            v.back().first  = (v.back().first == 'R' ? 'L' : 'R');
        }
    }
}

bool compress(string &rots) {
    if(rots.length() <= 2) return false;
    vector<pair<char, int>> v;
    v.push_back(pair<char, int>(rots[0], 1));
    for(int ii = 1; ii < rots.length(); ii++) {
        if(v.back().first != rots[ii]) {
            helper(v);
            v.push_back(pair<char, int>(rots[ii], 1));
        } else v.back().second++;
    }
    helper(v);

    rots = "";
    int jj;
    for(int ii = 0; ii < v.size(); ii += 2) {
        if(ii == v.size() - 1) {
            for(jj = 0; jj < v[ii].second; jj++)
                rots += v[ii].first;

        } else if(v[ii].first == v[ii + 1].first) {
            for(jj = 0; jj < v[ii].second + v[ii + 1].second; jj++)
                rots += v[ii].first;

        } else { // if(v[ii].first != v[ii + 1].first) {
            if(v[ii].second > v[ii + 1].second)
                rots += v[ii].first;
            else if(v[ii].second < v[ii + 1].second)
                rots += v[ii + 1].first;
        }
    }

    return true;
}

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

    // works but runtime error
    // while(compress(rots)) { }
    compress(rots)

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
