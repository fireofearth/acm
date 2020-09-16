#include <bits/stdc++.h>
using namespace std;

char encode(char ch, int key) {
    ch = ((ch - 'A') + (key - 'A') + 26 ) % 26;
    ch += 'A';
    return ch;
}

char decode(char ch, char key) {
    ch = ((ch - 'A') - (key - 'A') + 26 ) % 26;
    ch += 'A';
    return ch;
}

/*
g++ -std=c++11 f-drunk.cpp -o k
*/
int main() {
    string K, C, out;
    cin >> C >> K;
    int n = K.size();
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            out += decode(C[i], K[i]);
        } else {
            out += encode(C[i], K[i]);
        }
    }
    cout << out << endl;
    return 0;
}

