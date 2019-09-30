#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
using namespace std;

/*

g++ -std=c++11 b-balanced2.cpp -o k
1 to 2*10^5 strings

5 
TheStrong 90 60 10 
TheInvincible 10000 10000 10000 
TheTough 70 50 25 
TheBrick 3 1 4159 
TheResilient 160 40 10
*/

void debug() {
    cout << "DEBUG" << endl;
}

int i_beats_j(int hpi, int ati, int dfi, int hpj, int atj, int dfj) {
    if(atj - dfi <= 0 && ati - dfj <= 0) {
        return 0;
    } else if(atj - dfi <= 0) {
        return 1;
    } else if(ati - dfj <= 0) {
        return -1;
    } else {
        if(hpi / (atj - dfi) == hpj / (ati - dfj)) {
            return 0;
        } else if(hpi / (atj - dfi) > hpj / (ati - dfj)) {
            return 1;
        } else {
            return -1;
        }
    }
}

int main() {
    int N;
    cin >> N;
    string name[N];
    int HP[N];
    int AT[N];
    int DF[N];
    //bool b[N][N]; // b[i][j] == true iff i beats j
    set<int> b[N];
    bool tmp;
    for(int i = 0; i < N; i++) {
        cin >> name[i] >> HP[i] >> AT[i] >> DF[i];
        b[i] = set<int>();
    }

    if(N < 3) {
        cout << 0 << endl;
        return 0;
    }

    for(int i = 0; i < N; i++) {
        // compare against fighter
        for(int j = i + 1; j < N; j++) {
            tmp = i_beats_j(HP[i], AT[i], DF[i], HP[j], AT[j], DF[j]);
            if(tmp == 1) {
                b[i].insert(j);
            } else if(tmp == -1) {
                b[j].insert(i);
            }
        }
    }

    for(int i = 0; i < N; i++) {
        cout << i << ": ";
        for(int j : b[i]) cout << j << " ";
        cout << endl;
    }

    debug();

    set<set<int>> touched;
    set<int> tmps;
    for(int i = 0; i < N; i++) {
        for(int j : b[i]) {
            for(int k : b[j]) {
                cout << i << " " << j << " " << k << " " << b[k].count(i) << endl;
                if(b[k].count(i) != 0) {
                    // we found it
                    tmps = set<int>();
                    tmps.insert(i);
                    tmps.insert(j);
                    tmps.insert(k);
                    if(touched.count(tmps) == 0) {
                        cout << name[i] << " " << name[j] << " " << name[k] << endl;
                        touched.insert(tmps);
                    }
                }
            }
        }
    }

    return 0;
}

