#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<int>::max();

void debug() { cout << "DEBUG" << endl; }

template<class T>
void print(T msg) { cout << msg << endl; }

typedef pair<int, int> P;

struct by_first {
    bool operator() (const vector<int> &a,
            const vector<int> &b) {
        return a[0] < b[0];
    }
};

/*
g++ -std=c++11 c-commuting.cpp -o k

1 -> 6
2 -> 3
3 -> 2
4 -> 5
5 -> 4
6 -> 7
7 -> 8
8 -> 1

8
6 3 2 5 4 7 8 1

1 -> 7
2 -> 3
3 -> 5
4 -> 2
5 -> 4
6 -> 1
7 -> 8
8 -> 6

8
7 3 5 2 4 1 8 6
*/
int main() {
    freopen("commuting.in", "r", stdin);
    freopen("commuting.out", "w", stdout);

    int n, i, j, k;
    cin >> n;
    int f[n+1];
    int g[n+1];
    bool seen[n+1];
    vector<int> cycle;
    vector<int> *pcycle;
    vector<int>::iterator vit;
    vector<vector<vector<int>>> cycles(n+1);
    vector<vector<int>>::iterator sit;
    set<int> s;
    set<int> t;
    for(i = 1; i < n+1; i++) {
        cin >> f[i];
        g[i] = 0;
        seen[i] = false;
    }

    // make cycles
    for(i = 1; i < n+1; i++) {
        if(seen[i] == false) {
            cycle = vector<int>();
            j = i;
            do {
                seen[j] = true;
                cycle.push_back(j);
                j = f[j];
            } while(i != j);
            k = cycle.size();
            cycles[k].push_back(cycle);
            s.insert(k);
            t.insert(k);
        }
    }

    /*
    // list the cycles
    for(const vector<vector<int>> &cs : cycles) {
        for(const vector<int> &c : cs) {
            for(int p : c) {
                cout << p << " ";
            }
            cout << endl;
        }
    }
    */

    for(int i : s) {
        pcycle = NULL;
        for(int j : t) {
            if(i % j == 0) {
                if(j >= i) break;
                if(!pcycle || pcycle->at(0) > cycles[j][0][0]) {
                    pcycle = &cycles[j][0];
                }
            }
        }

        if(pcycle && pcycle->at(0) < cycles[i][0][0]) {
            // use pcycle representing cycle with order dividing i
            for(const vector<int> &c : cycles[i]) {
                vit = pcycle->begin();
                for(int p : c) {
                    g[p] = *vit;
                    vit++;
                    if(vit == pcycle->end()) vit = pcycle->begin();
                }
            }
            t.erase(i);
        } else {
            // use first cycle of order i
            pcycle = &cycles[i][0];
            for(sit = cycles[i].begin(); sit != cycles[i].end(); sit++) {
                for(j = 0; j < pcycle->size(); j++)
                    g[sit->at(j)] = pcycle->at(j);
            }
        }
    }
    
    for(i = 1; i < n+1; i++) {
        cout << g[i];
        if(i == n) cout << endl;
        else cout << " ";
    }
    
    /*
    // test f, g commute
    for(i = 1; i < n+1; i++) {
        cout << f[g[i]];
        if(i == n) cout << endl;
        else cout << " ";
    }
    for(i = 1; i < n+1; i++) {
        cout << g[f[i]];
        if(i == n) cout << endl;
        else cout << " ";
    }
    */

    return 0;
}











