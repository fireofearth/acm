#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <utility>
using namespace std;

/*
https://stackoverflow.com/questions/522778/caesar-cipher-in-c
g++ -std=c++11 a-abnormal.cpp -o k
*/

void debug() {
    cout << "DEBUG" << endl;
}

char encode(char ch, int key) {
    ch -= 'a';
    ch = ( ch + key + 26 ) % 26;
    ch += 'a';
    return ch;
}

char decode(char ch, int key) {
    ch -= 'a';
    ch = ( ch - key + 26 ) % 26;
    ch += 'a';
    return ch;
}

int main() {
    char e;
    int s;
    string w;
    cin >> e >> s >> w;
    for(int i = 0; i < w.size(); i++) {
        if(e == 'E')
            w[i] = encode(w[i], s);
        else
            w[i] = decode(w[i], s);
    }
    cout << w << endl;
    return 0;
}
