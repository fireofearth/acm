#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long int mlong;

/*
g++ -std=c++11 -o k test.cpp
*/

void debug() {
    cout << "DEBUG" << endl;
}

int main() {
    int n; string input;
    cin >> n;
    cin >> input;
    //getline(cin, input);
    cout << n << "%" << endl;
    cout << input << "%" << endl;
}
