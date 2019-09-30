#include <iostream>
#include <string>
#include <cctype>
using namespace std;

/*

g++ -std=c++11 a-a-plus-b.cpp -o k
1 to 2*10^5 strings
*/

void debug() {
    cout << "DEBUG" << endl;
}


char change_case (char c, int i) {
    if (i != 0) 
        return std::tolower(c); 
    else
        return std::toupper(c); 
}

int main() {
    // concatenate b before a and change case
    string a, b, c;
    cin >> a; cin >> b;
    c = b + a;
    for(int i = 0; i < c.size(); i++) {
        c[i] = change_case(c[i], i);
    }
    cout << c << endl;

    return 0;
}
