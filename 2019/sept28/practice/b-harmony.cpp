#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <utility>
using namespace std;

/*

g++ -std=c++11 b-harmony.cpp -o k
1 to 2*10^5 strings
*/

void debug() {
    cout << "DEBUG" << endl;
}

// "larger" or "higher", "smaller" or "lower"
// p : q <=> p/q
pair<string, string> notes[] = {
    make_pair("A", "G#"), // -11
    make_pair("A", "G"), // -10
    make_pair("A", "F#"), // -9
    make_pair("A", "F"), // -8
    make_pair("A", "E"), // -7
    make_pair("A", "D#"), // -6
    make_pair("A", "D"), // -5
    make_pair("A", "C#"), // -4
    make_pair("A", "C"), // -3
    make_pair("A", "B"), // -2
    make_pair("A", "A#"), // -1
    make_pair("A", "A"), // 0
    make_pair("A", "G#"), // 1
    make_pair("F", "G"), // 2
    make_pair("A", "F#"), // 3
    make_pair("A", "F"), // 4
    make_pair("A", "E"), // 5
    make_pair("A", "D#"), // 6
    make_pair("A", "D"), // 7
    make_pair("A", "C#"), // 8
    make_pair("A", "C"), // 9
    make_pair("A", "B"), // 10
    make_pair("A", "A#") // 11
};

int main() {
    // concatenate b before a and change case
    int p, q;
    cin >> p; cin >> q;
    float c = log2( ((float) p) / ((float) q) );
    int c1, c2;
    string a1, a2;

    c = c - trunc(c);
    c = 12 * c;
    int i = -11;
    for(; i < 12; i++) {
        if((-0.5 - 0.006 <= c - ((float) i)) && (c - ((float) i) <= 0.5 + 0.006)) {
            break;
        }
    }

    c = 100.0*(c - ((float) i));
    int j = -50;
    for(; j < 51; j++) {
        if(-0.6 <= c - ((float) j) && c - ((float) j) <= 0.6) {
            break;
        }
    }
    
    if(j >= 25) {
        c1 = 25; c2 = -(j - 25);
    } else if(j >= 0) {
        c1 = j; c2 = 0;
    } else if(j >= -24) {
        c1 = 0; c2 = -j;
    } else { // j >= -50
        c1 = j + 25; c2 = 25;
    }

    pair<string, string> note = notes[i + 11];
    a1 = note.first; a2 = note.second;
    cout << a1 << " " << c1 << endl;
    cout << a2 << " " << c2 << endl;

    return 0;
}

