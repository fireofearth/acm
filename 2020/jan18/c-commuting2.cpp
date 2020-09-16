#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
lld MAX = numeric_limits<int>::max();

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

void debug() { cout << "DEBUG" << endl; }

template<class T>
void print(T msg) { cout << msg << endl; }

typedef pair<int, int> P;

struct CycleNode {
    vector<P*> items;
};

struct by_second {
    bool operator() (const P &a, const P &b) {
        return a.second < b.second;
    }
};

struct by_front {
    bool operator() (const set<P, by_second> &a,
            const set<P, by_second> &b) {
        return a.begin()->second < b.begin()->second;
    }
};

int main() {
    //freopen("commuting.in", "r", stdin);
    //freopen("commuting.out", "w", stdout);

    int n, i, j, k;
    cin >> n;
    int f[n+1];
    int g[n+1];
    bool seen[n+1];
    set<P, by_second> cycle;
    set<P, by_second> *pcycle;
    set<P, by_second>:: iterator it
    vector<set<set<P, by_second>, by_front>> cycles(n+1);
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
            cycle = set<P, by_second>();
            j = i;
            do {
                cycle.insert(P(j, f[j]));
                j = f[j];
            } while(i != j);
            k = cycle.size();
            cycles[k].insert(cycle);
            s.insert(k);
            t.insert(k);
        }
    }

    for(const set<set<P, by_second>, by_front> &cs : cycles) {
        for(const set<P, by_second> &c : cs) {
            for(const P &p : c) {
                cout << p.first << " => " << p.second << "\n";
            }
            cout << endl;
        }
    }

    for(int i : s) {
        pcycle = NULL;
        for(int j : t) {
            if(j >= i) break;
            if(!pcycle && pcycle->begin()->second > cycles[j].begin()->second)
                pcycle = &(cycles[j]);
        }

        if(pcycle && pcycle->begin()->second < cycles[i].begin()->second) {
            it = pcycle->begin();
            for(const set<P, by_second> &c : cycles[i]) {
                for(const P &p : c) {
                    g[p.first] = it->second;
                    it++;
                    if(it == pcycle->end()) it = pcycle->begin();
                }
            }
        } else {
            // go through all cycles of size i and write g with lowest cycle of size i
        }
    }
    
    return 0;
}
