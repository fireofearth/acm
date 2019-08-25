#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
g++ -std=c++11 -o k a-mentalrotation3.cpp

1 <= N <= 1000; S =(L,R)+ up to 100 times
NxN array

1 L
>

2 R
..
>>

3 R
>vv
.v.
<<v

3 R
^.v
^v<
<.<

3 RLLLLRLLLR
>vv
.v.
<<v

3 RLLLLRLLLLR
>vv
.v.
<<v

4 R
.>.>
v.v.
^.^^
<<<<

4 L
.>.>
v.v.
^.^^
<<<<

4 LLRR
.>.>
v.v.
^.^^
<<<<
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

char right(char c) {
    if(c == '.') return c;
    for(int i = 0; i < 4; i++)
        if(arrs[i] == c) return arrs[(i + 1) % 4];
    return 'X';// should not happen
}

char left(char c) {
    if(c == '.') return c;
    for(int i = 0; i < 4; i++)
        if(arrs[i] == c) return arrs[i - 1 < 0 ? 3 : i - 1];
    return 'X';// should not happen
}

inline void cyclic_roll(char &a, char &b, char &c, char &d, bool r) {
    if(r) {
        char temp = a;
        a = right(b);
        b = right(c);
        c = right(d);
        d = right(temp);
    } else {
        char temp = a;
        a = left(d);
        d = left(c);
        c = left(b);
        b = left(temp);
    }
}

void rotate(char **m, int n, bool r) {
    for(int i=0; i<n/2; i++)
       for(int j=0; j<(n+1)/2; j++)
           cyclic_roll(m[i][j], m[n-1-j][i], m[n-1-i][n-1-j], m[j][n-1-i], r);
    if(n % 2 == 1) {
        if(r)
            m[n/2][n/2] = right(m[n/2][n/2]);
        else
            m[n/2][n/2] = left(m[n/2][n/2]);
    }
}

int main() {
    int n; string rots;
    cin >> n;
    cin >> rots;
    char *map[n];
    for(int i = 0; i < n; i++) {
        // n + 1 b/c inputs may insert null-terminating characters
        map[i] = new char[n + 1];
        cin >> map[i];
    }

    while(compress(rots)) { }

    for(int i = 0; i < rots.length(); i++) {
        if(rots[i] == 'R')
            rotate(map, n, true);
        else
            rotate(map, n, false);
    }

    for(int i = 0; i < n; i++)
        cout << map[i] << endl;

    return 0;
}

