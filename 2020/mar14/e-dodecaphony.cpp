#include <bits/stdc++.h>
using namespace std;

map<string, int> m = {
    {"C",  0},
    {"C#", 1},
    {"D",  2},
    {"D#", 3},
    {"E",  4},
    {"F",  5},
    {"F#", 6},
    {"G",  7},
    {"G#", 8},
    {"A",  9},
    {"A#", 10},
    {"B",  11},
};

int N = 12;

bool is_transposition(int l, vector<int> a, vector<int> b) {
    bool is;
    for(int i = 0; i < 12; i++) {
        is = true;
        for(int j = 0; j < l; j++)
            if((a[j] + i) % N != b[j]) is = false;
        if(is) return true;
    }
    return false;
}

bool is_retrograde(int l, vector<int> a, vector<int> b) {
    bool is = true;
    for(int i = 0; i < l; i++) {
        if(a[i] != b[l - i - 1]) is = false;
    }
    return is;
}

bool is_inversion(int l, vector<int> a, vector<int> b) {
    if(a[0] != b[0]) return false;
    bool is = true;
    int n;
    for(int i = 1; i < l; i++) {
        if((a[0] - (a[i] - a[0]) + N) % N != b[i]) is = false;
    }
    return is;
}

/*
g++ -std=c++11 e-dodecaphony.cpp -o k
*/
int main() {
    int i, l;
    string s;
    cin >> l;
    vector<int> a(l);
    vector<int> b(l);
    for(i = 0; i < l; i++) {
        cin >> s;
        a[i] = m[s];
    }
    for(i = 0; i < l; i++) {
        cin >> s;
        b[i] = m[s];
    }

    if(is_transposition(l, a, b)) {
        cout << "Transposition" << endl;
        return 0;
    } else if(is_retrograde(l, a, b)) {
        cout << "Retrograde" << endl;
        return 0;
    } else if(is_inversion(l, a, b)) {
        cout << "Inversion" << endl;
        return 0;
    } else {
        cout << "Nonsense" << endl;
        return 0;
    }
}

