#include <iostream>
#include <set>
#include <string>
#include <queue>
#include <vector>
using namespace std;

void debug() { printf("DEBUG\n"); }
void debug(int i) { printf("DEBUG: %d\n", i); }
void debug(string s) { printf("DEBUG: %s\n", s); }

struct B {
    int val;
    int depth;
    B *nxt;
    set<B *> prevs;
    B(int val) : val(val), depth(0), nxt(NULL) {}
};

struct SortMaster {
    bool operator()(const B *lhs, const B *rhs) const {
        return lhs->depth < rhs->depth;
    }
};

typedef priority_queue<B *, vector<B *>, SortMaster> pq;

void set_depth(B *b, int depth) {
    b->depth = depth;
    for(B *c: b->prevs)
        set_depth(c, depth + 1);
}

void top_sort_school(B **b, int n, int k) {
    pq noedge, tmp;
    int m, acc; acc = 0;
    B *c, *d;

    for(int i = 0; i < n; i++) {
        if(b[i]->prevs.empty())
            noedge.push(b[i]);
    }

    while(!noedge.empty()) {
        acc++;
        m = min(k, (int) noedge.size());

        for(int i = 0; i < m; i++) {
            c = noedge.top(); noedge.pop();
            d = c->nxt;
            if(d) {
                d->prevs.erase(c);
                if(d->prevs.empty())
                    tmp.push(d);
            }
        }

        while(!tmp.empty()) {
            noedge.push(tmp.top()); tmp.pop();
        }
    }

    cout << acc << endl;
}

/*
Yay I graduated. So it's apparently possible for heap structs to have set members, and sets of pointers.
g++ -std=c++11 g-graduation4.cpp -o k
*/
int main() {
    int n, k, t;
    cin >> n >> k;
    int a[n];
    B **b = new B*[n];
    set<B *> roots;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = new B(i);
    }

    for(int i = 0; i < n; i++) {
        if(a[i]) {
            t = a[i] - 1;
            b[i]->nxt = b[t];
            b[t]->prevs.insert(b[i]);
        } else {
            roots.insert(b[i]);
        }
    }

    for(B *root : roots)
        set_depth(root, 0);

    top_sort_school(b, n, k);

    return 0;
}
