#include<bits/stdc++.h>
using namespace std;

struct BTNode {
    int v;
    BTNode *l;
    BTNode *r;
    //BTNode *p;
};

struct Answer {
    int s; // size of the largest BST
    BTNode *n; // the root of the largest BST
};

void add_l_node(BTNode *p, BTNode *l) {
    p->l = l; //l->p = p;
}

void add_r_node(BTNode *p, BTNode *r) {
    p->r = r; //r->p = p;
}

BTNode* create_node(int i) {
    return new BTNode{i, NULL, NULL};//, NULL};
}

void reset_node(BTNode *n) {
    n->l = NULL; n->r = NULL; //n->p = NULL;
}

Answer largest_bst(BTNode *n) {
    if(!n) return Answer{0, NULL};
    bool l_ok, r_ok; l_ok = false; r_ok = false;
    Answer l = largest_bst(n->l);
    Answer r = largest_bst(n->r);
    if(!(n->l)) l_ok = true;
    else if((l.n == n->l) && (n->l->v <= n->v)) {
        l_ok = true;
    }
    if(!(n->r)) r_ok = true;
    else if((r.n == n->r) && (n->v <= n->r->v)) {
        r_ok = true;
    }
    if(l_ok && r_ok) return Answer{l.s + r.s + 1, n};
    else if(l.s < r.s) return r;
    else return l;
}

void in_order_print(BTNode *n) {
    if(!n) return;
    in_order_print(n->l);
    cout << n-> v << " ";
    in_order_print(n->r);
}

/**
Get largest subtree in binary tree that is a binary search tree
g++ -std=c++11 largest_bst.cpp -o k
*/
int main() {
    BTNode *r;
    BTNode *c;
    Answer a;
    vector<int> vals = {0, -1, 11, 12, 13, -2, 1, 2, 3, 4, 5, 6, -3,
        -4, 17, 18, 19, 20, 21, 22, 23, -5};
    int n = vals.size();
    vector<BTNode *> v(n + 1);
    for(int i = 1; i <= n; i++) {
        v[i] = create_node(vals[i]);
    }

    cout << ">>> test 1" << endl;
    r = v[12];
    add_l_node(v[12], v[5]);
    add_r_node(v[12], v[21]);

    add_l_node(v[5], v[1]);
    add_r_node(v[5], v[10]);

    add_l_node(v[21], v[13]);

    add_l_node(v[1], v[3]);

    add_l_node(v[3], v[2]);
    add_r_node(v[3], v[4]);

    a = largest_bst(r);
    cout << "largest BST subtree has size " << a.s << endl;
    in_order_print(a.n);
    cout << endl;

    cout << ">>> test 2" << endl;

    add_l_node(v[10], v[7]);
    add_r_node(v[10], v[11]);

    add_l_node(v[7], v[6]);
    add_r_node(v[7], v[9]);

    add_l_node(v[9], v[8]);

    a = largest_bst(r);
    cout << "largest BST subtree has size " << a.s << endl;
    in_order_print(a.n);
    cout << endl;

    add_r_node(v[13], v[17]);

    add_l_node(v[17], v[15]);
    add_r_node(v[17], v[19]);

    add_l_node(v[15], v[14]);
    add_r_node(v[15], v[16]);

    add_l_node(v[19], v[18]);
    add_r_node(v[19], v[20]);

    a = largest_bst(r);
    cout << "largest BST subtree has size " << a.s << endl;
    in_order_print(a.n);
    cout << endl;

    v[17]->v = -6;

    a = largest_bst(r);
    cout << "largest BST subtree has size " << a.s << endl;
    in_order_print(a.n);
    cout << endl;

    return 0;
}
