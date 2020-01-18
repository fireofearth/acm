#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<lld>::max();

/*
g++ -std=c++11 f-lcs.cpp -o k
*/
int main() {
    string s;
    string t;
    cin >> s >> t;
    int sn = s.size() + 1;
    int tn = t.size() + 1;
    // s by t
    int m[sn][tn];
    for(int i = 0; i < sn; i++)
        m[i][0] = 0;

    for(int j = 1; j < tn; j++)
        m[0][j] = 0;

    for(int i = 1; i < sn; i++) {
        for(int j = 1; j < tn; j++) {
            if(s[i-1] == t[j-1]) {
                m[i][j] = m[i-1][j-1] + 1;
            } else {
                m[i][j] = max(m[i][j-1], m[i-1][j]);
            }
        }
    }

    string o = "";
    int i = s.size();
    int j = t.size();
    while(i > 0 && j > 0) {
        if(m[i][j] == m[i][j-1]) {
            j--;
        } else if(m[i][j] == m[i-1][j]) {
            i--;
        } else {
            o = s[i-1] + o;
            i--;
            j--;
        }
    }
    cout << o << endl;

    return 0;
}
