#include<iostream>
#include<vector>
using namespace std;

typedef unsigned long long int mlong;


/**
g++ -std=c++11 d-missing.cpp -o k
4
3
4
5
8
*/

int main() {
    int n, c, d;
    vector<int> v;
    cin >> n;
    int last;
    bool skipped = false;
    for(int i = 0; i < n; i++) {
        cin >> c;
        if(i == 0) {
            // check if c == 1
            for(int j = 1; j < c; j++)
                v.push_back(j);
        } else {
            for(int j = last + 1; j < c; j++)
                v.push_back(j);
        }
        last = c;
    }
    if(v.empty()) {
        cout << "good job" << endl;
        return 0;
    }
    for(int i : v) {
        cout << i << endl;
    }
    return 0;
}

