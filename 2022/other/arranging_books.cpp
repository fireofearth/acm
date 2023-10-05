#include <bits/stdc++.h>
using namespace std;

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

/*
g++ -std=c++11 arranging_books.cpp -o k
*/
int main() {
    int i, j, k;
    string s;
    cin >> s;
    int n_L = 0;
    int n_M = 0;
    int n_S = 0;
    int n_swaps = 0;
    vector<char> v;
    for(char c : s) {
        if(c == 'L') n_L++;
        if(c == 'M') n_M++;
        if(c == 'S') n_S++;
        v.push_back(c);
    }

    // move L's
    int subarr_L = 0;
    int beg = n_L;
    int end = v.size() - 1;
    while(subarr_L < n_L) {
        if(v[subarr_L] == 'L') subarr_L++;
        else if(v[subarr_L] == 'S') {
            while(v[end] != 'L') end--;
            swap(v[subarr_L], v[end]);
            n_swaps++;
        } else {
            // v[subarr_L] == 'M'
            while(v[beg] != 'L') beg++;
            swap(v[subarr_L], v[beg]);
            n_swaps++;
        }
    }

    // move S's
    int subarr_M = n_L;
    beg = n_L + n_M;
    end = n_L + n_M;
    while(subarr_M < end) {
        if(v[subarr_M] == 'M') subarr_M++;
        else {
            while(v[beg] != 'M') beg++;
            swap(v[subarr_M], v[beg]);
            n_swaps++;
        }
    }
    cout << n_swaps << "\n";
    return 0;
}
