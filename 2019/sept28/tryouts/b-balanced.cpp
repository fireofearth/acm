#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

/*
g++ -std=c++11 b-balanced.cpp -o k
SUCCESS!

1 
TheStrong 90 60 10 

5 
TheStrong 90 60 10 
TheInvincible 10000 10000 10000 
TheTough 70 50 25 
TheBrick 3 1 4159 
TheResilient 160 40 10

10 
TheStrong 90 60 10 
TheInvincible 10000 10000 10000 
TheTough 70 50 25 
TheBrick 3 1 4159 
TheResilient 160 40 10
2TheStrong 90 60 10 
2TheInvincible 10000 10000 10000 
2TheTough 70 50 25 
2TheBrick 3 1 4159 
2TheResilient 160 40 10
*/

void debug() {
    cout << "DEBUG" << endl;
}

bool i_beats_j(int hpi, int ati, int dfi, int hpj, int atj, int dfj) {
    if(atj - dfi <= 0 && ati - dfj <= 0) {
        return false;
    } else if(atj - dfi <= 0) {
        return true;
    } else if(ati - dfj <= 0) {
        return false;
    } else {
        if(ceil( ((float) hpi) / (atj - dfi)) == ceil( ((float) hpj) / (ati - dfj))) {
            return false;
        } else if(ceil( ((float) hpi) / (atj - dfi)) > ceil( ((float) hpj) / (ati - dfj))) {
            return true;
        } else {
            return false;
        }
    }
}

int main() {
    int N, acc; acc = 0;
    vector<string> sol;
    cin >> N;
    string name[N];
    int HP[N];
    int AT[N];
    int DF[N];
    set<int> b[N];
    for(int i = 0; i < N; i++) {
        cin >> name[i] >> HP[i] >> AT[i] >> DF[i];
        b[i] = set<int>();
    }

    if(N < 3) {
        cout << 0 << endl;
        return 0;
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(i != j && i_beats_j(HP[i], AT[i], DF[i], HP[j], AT[j], DF[j]))
                b[i].insert(j);

    set<set<int>> touched;
    set<int> tmps;
    for(int i = 0; i < N; i++) {
        for(int j : b[i]) {
            for(int k : b[j]) {
                if(b[k].count(i) != 0) {
                    tmps = set<int>({i, j, k});
                    if(touched.count(tmps) == 0) {
                        acc += 1;
                        sol.push_back(name[i] + " " + name[j] + " " + name[k]);
                        touched.insert(tmps);
                    }
                }
            }
        }
    }

    cout << acc << endl;
    for(const string& str : sol) {
        cout << str << endl;
    }

    return 0;
}
