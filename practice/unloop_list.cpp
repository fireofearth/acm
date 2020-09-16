#include <bits/stdc++.h>
using namespace std;

struct NotALoopException : public exception {
	const char * what () const throw () {
    	return "List is not a loop";
    }
};

struct EmptyListException : public exception {
    const char * what () const throw () {
        return "List is empty";
    }
};

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

int loop_len(Node *root) {
    Node *p0 = root; // show ptr
    Node *p1 = root; // fast ptr
    int n = 0;

    do {
        if(!(p1 && p1->n && p1->n->n)) {
            throw NotALoopException();
        }
        p0 = p0->n;
        p1 = p1->n->n;
    } while(p0 != p1);
    do {
        n++;
        p1 = p1->n;
    } while(p0 != p1);
    return n;
}

Node *unloop(Node *root) {
    if(!root) {
        throw EmptyListException();
    }
    int len;
    Node *p0 = root;
    Node *p1 = root;
    try {
        len = loop_len(root);
    } catch(const NotALoopException& e) {
        // just return the end of the list.
        while(p1->n) {
            p1 = p1->n;
        }
        return p1;
    }

    for(int i = 0; i < len - 1; i++) {
        p1 = p1->n;
    }
    // edge case where loop entrance is the root
    if(p1->n == root) {
        p1->n = NULL;
        return p1;
    }
    p1 = p1->n;
    while(p0->n != p1->n) {
        p0 = p0->n;
        p1 = p1->n;
    }
    p1->n = NULL;
    return p1;
}

/**
g++ -std=c++11 unloop_list.cpp -o k
*/
int main() {
    int N = 7;
    int l = 0;
    cin >> N;
    cin >> l;
    int a[N];
    for(int i = 0; i < N; i++) {
        a[i] = i;
    }

    Node *root, *c;
    Node *p = NULL;
    for(int i = 0; i < N; i++) {
        if(i == 0) {
            root = new Node{a[0],NULL};
            c = root;
        } else {
            c->n = new Node{a[i],NULL};
            c = c->n;
        }
        if(i == l) p = c;
    }
    if(p) {
        c->n = p;
    }

    cout << "calling loop_len" << endl;
    try {
    cout << "loop len: "<<  loop_len(root) << endl;
    } catch(const NotALoopException& e) {
        cout << "exception: " << e.what() << endl;
    }
    cout << "calling unloop" << endl;
    try {
        cout << "last item: " << unloop(root)->v << endl;
    } catch(const EmptyListException& e) {
        cout << "exception: " << e.what() << endl;
    }
    print_list(root);

    return 0;
}
