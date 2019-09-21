#include <iostream>
#include <string>
#include <cctype>
using namespace std;

typedef unsigned long long int mlong;

/*

g++ -std=c++11 i-prefix.cpp -o k
1 to 2*10^5 strings
*/

int main() {
    string t;
    cin >> t;
    bool read = false;
    for(char & c : t) {
        if(isdigit(c)) {
            cout << c;
            read = true;
        } else {
            break;
        }
    }
    if(!read)
        cout << -1 << endl;
    else
        cout << endl;
    return 0;
}

