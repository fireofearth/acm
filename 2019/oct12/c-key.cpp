#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <utility>
using namespace std;

void debug() {
    cout << "DEBUG" << endl;
}

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

// INV: in.size() <= key.size()
string decode_substr(string in, string key) {
    string out;
    for(int i = 0; i < in.size(); i++) {
        out += decode(in[i], key[i]);
    }
    return out;
}

/*
https://stackoverflow.com/questions/522778/caesar-cipher-in-c
g++ -std=c++11 c-key.cpp -o k

SGZVQBUQAFRWSLC ACM
SGZVQBUQAFR ACM
SGZVQBUQ ACM
SGZ ACM
*/
int main() {
    string in, out, key;
    int k = 0;
    cin >> in >> key;
    int m = key.size();
    while(k < in.size()) {
        out += decode_substr(in.substr(k, min(m, (int) in.size() - k)), key);
        key = out.substr(k, m);
        k += m;
    }
    cout << out << endl;

    return 0;
}
