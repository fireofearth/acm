#include<bits/stdc++.h>
using namespace std;

struct BTNode {
    int v;
    BTNode *l;
    BTNode *r;
    BTNode *p;
};

BTNode* next_in_order(BTNode *n) {
    if(n->r) {
        n = n->r;
        while(n->l)
            n = n->l;
        return n;
    }
    BTNode *p;
    while(n->p) {
        p = n->p;
        if(p->l == n) {
            return p;
        } else {
            // n is p's right child
            n = p;
        }
    }
    return NULL;
}

void add_l_node(BTNode *p, BTNode *l) {
    p->l = l; l->p = p;
}

void add_r_node(BTNode *p, BTNode *r) {
    p->r = r; r->p = p;
}

void reset_node(BTNode *n) {
    n->l = NULL; n->r = NULL; n->p = NULL;
}

/**
Get the next element of binary tree in order traversal given a single binary tree node.
Every node has a pointer to their parent.
g++ -std=c++11 next_in_order.cpp -o k
*/
int main() {
    BTNode *r;
    BTNode *c;
    int n = 10;
    vector<BTNode *> v(n + 1);
    for(int i = 1; i <= n; i++) {
        v[i] = new BTNode{i, NULL, NULL, NULL};
    }

    cout << ">>> test 1" << endl;
    r = v[7];
    add_l_node(v[7], v[3]);
    add_r_node(v[7], v[8]);
    add_l_node(v[3], v[1]);
    add_r_node(v[3], v[5]);
    add_r_node(v[1], v[2]);
    add_l_node(v[5], v[4]);
    add_r_node(v[5], v[6]);
    add_l_node(v[8], v[9]);

    for(int i = 1; i <= 9; i++) {
        c = next_in_order(v[i]);
        if(c) cout << v[i]->v << "'s next in order is " << c->v << endl;
        else cout << v[i]->v << " does not have a next in order" << endl;
    }
    for(int i = 1; i <= 9; i++) {
        reset_node(v[i]);
    }

    cout << ">>> test 2" << endl;
    r = v[2];
    add_l_node(v[2], v[1]);
    add_r_node(v[2], v[5]);
    add_l_node(v[5], v[4]);
    add_l_node(v[4], v[3]);
    add_r_node(v[5], v[6]);

    for(int i = 1; i <= 6; i++) {
        c = next_in_order(v[i]);
        if(c) cout << v[i]->v << "'s next in order is " << c->v << endl;
        else cout << v[i]->v << " does not have a next in order" << endl;
    }

    return 0;
}
