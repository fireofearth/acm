#include<iostream>
#include<vector>
#include<string>
using namespace std;

int min_3(int a, int b, int c) {
    return min(a, min(b, c));
}

void prt(vector<vector<int>>& distance) {
    for(vector<int>& v : distance) {
        for(int d : v) {
            cout << d;
        }
        cout << endl;
    }
    cout << endl;
}

/**
g++ -std=c++11 edit_distance.cpp -o k

saturday
sunday
3

abcabc
cba
4

abcd
cde
3
*/
int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> distance(m + 1, vector<int>(n + 1, 0));
    for(int i = 0; i <= n; i++) {
        distance[0][i] = i;
    }
    for(int j = 0; j <= m; j++) {
        distance[j][0] = j;
    }
    //prt(distance);
    for(int j = 1; j <= m; j++) {
        for(int i = 1; i <= n; i++) {
            // find distance of substr (i, j)
            // str are zero indixed whereas our distance table indices (i,j) refer to sizes of substrings
            if(s1[i - 1] == s2[j - 1]) {
                distance[j][i] = distance[j - 1][i - 1];
            } else {
                distance[j][i] = min_3(
                    // substitution
                    1 + distance[j - 1][i - 1],
                    // addition
                    // we add letter to s1
                    1 + distance[j - 1][i],
                    // deletion
                    1 + distance[j][i - 1]
                );
            }
        }
    }
    cout << distance[m][n] << endl;

    return 0;
}
