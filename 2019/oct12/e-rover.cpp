#include <iostream>
#include <string>
#include <unordered_set>
#include <cmath>
#include <utility>
using namespace std;
 
void debug() {
    cout << "DEBUG" << endl;
}
 
/*
* passed all the tests *

NESW
o: 4

WNEENWEENEENE
o: 10

EEEEEEEEE
o: 6

NEWSNEWSSNEWNEWSSS
o: 13

NESWSENWSESN
o: 11

NSEWESN
o: 7

SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
o: 21

g++ -std=c++11 e-rover.cpp -o k
*/
int main() {
    string in, tmp;
    int acc = 0;
    int c, d;
    size_t pos;
    unordered_set<string> s;
    cin >> in;
    // substr of size i
    for(int i = 2; i < in.size(); i++) {
        s = unordered_set<string>();
        // substr starting at pos j
        for(int j = 0; j < in.size(); j++) {
            // reached the end of line
            if( j > ((int) in.size()) - i ) break;
            tmp = in.substr(j, i);
            // searched this substr before, skip.
            if( s.count(tmp) ) continue;
            s.insert(tmp);
            pos = in.find(tmp, j + i);
            c = 0;
            while(pos != string::npos) {
                c++;
                pos = in.find(tmp, pos + i);
            }
            if(c > 0) {
                d = in.size() - ((c + 1) * (i - 1)) + i;
                if(acc == 0 || acc > d) acc = d;
            }
        }
    }
    
    if(acc) cout << acc << endl;
    else cout << in.size() << endl;
 
    return 0;
}
