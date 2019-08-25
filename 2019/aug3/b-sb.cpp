#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long int mlong;

/*
g++ -std=c++11 -o k b-sb.cpp
SpongeBob SquarePants
*/


void debug() {
    cout << "DEBUG" << endl;
}

int main() {
    int T;
    cin >> T;
    int w[T]; int h[T];
    for(int i = 0; i < T; i++)
        cin >> w[i] >> h[i];
    for(int i = 0; i < T; i++)
        cout << (w[i] == h[i] ? "YES" : "NO") << endl;

    return 0;
}
