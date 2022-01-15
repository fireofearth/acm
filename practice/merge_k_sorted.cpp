#include<bits/stdc++.h>
using namespace std;

/**
Merge k sorted lists

Input:
line 1 integer k where 1 <= k is the number of sorted lists.
line 2..(k+1) intergers n_j a_1 a_2 ... a_n_j where 1 <= n_j
    is the size of the lists and a_1 .... a_n_j are the
    integer elements of that list

g++ -std=c++11 merge_k_sorted.cpp -o k

Examples:

2
3 1 3 5
3 2 4 6
o: 1 2 3 4 5 6

4
3 4 5 6
3 1 2 3
3 10 11 12
3 7 8 9
o: 1 2 3 4 5 6 7 8 9 10 11 12

*/
struct LNode {
    int v;
    struct LNode *n;
};

bool node_comp(LNode* lhs, LNode* rhs) {
    return lhs->v > rhs->v;
}

int main() {
    int i, j;
    int k, n, m;
    priority_queue<LNode*, vector<LNode*>, decltype(&node_comp)> pq(node_comp);
    // k sorted lists
    cin >> k;
    vector<LNode*> vl(k);
    LNode* c;
    vector<int> o;
    for(i = 0; i < k; i++) {
        cin >> n; // length of list i
        c = NULL;
        for(j = 0; j < n; j++) {
            cin >> m; // value of j-th cell in list i
            if(c) {
                c->n = new LNode{m, NULL};
                c = c->n;
            } else {
                c = new LNode{m, NULL};
                vl[i] = c;
            }
        }
    }

    for(i = 0; i < k; i++) {
        pq.push(vl[i]);
    }

    while(!pq.empty()) {
        c = pq.top();
        pq.pop();
        o.push_back(c->v);
        if(c->n) {
            pq.push(c->n);
        }
    }

    for(i = 0; i < o.size(); i++) {
        cout << o[i];
        if(i == o.size() - 1) cout << endl;
        else cout << " ";
    }

    return 0;
}
