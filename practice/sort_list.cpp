#include <bits/stdc++.h>
using namespace std;

struct Node {
    int v;
    Node *n;
};

void print_list(Node *root) {
    Node *c = root;
    while(c) {
        cout << c->v << " ";
        c = c->n;
    }
    cout << endl;
}

void insertion_sort(Node *&root) {
    if(!root) return;
    if(!root->n) return;
    Node *p0;
    Node *p1 = root;
    Node *c = p1->n;
    while(c) {
        p0 = root;
        //print_list(root);
        //cout << "DEBUG p0 " << p0->v << endl;
        //cout << "DEBUG p1 " << p1->v << endl;
        //cout << "DEBUG c " << c->v << endl;
        if(c->v < p0->v) {
            p1->n = c->n;
            c->n = root;
            root = c;
        } else if(p1->v <= c->v) {
            p1 = p1->n;
        } else {
            while(p0 != p1) {
                if(c->v <= p0->n->v) {
                    p1->n = c->n;
                    c->n = p0->n;
                    p0->n = c;
                    break;
                }
                p0 = p0->n;
            }
        }
        c = p1->n;
    }
}

/**


g++ -std=c++11 sort_list.cpp -o k
*/
int main() {
    int N = 6;
    cin >> N;
    int a[N] = {3,1,4,2,6,5};
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    Node *root, *c;
    root = new Node{a[0],NULL};
    c = root;
    for(int i = 1; i < N; i++) {
        c->n = new Node{a[i],NULL};
        c = c->n;
    }
    print_list(root);
    insertion_sort(root);
    print_list(root);
    return 0;
}

