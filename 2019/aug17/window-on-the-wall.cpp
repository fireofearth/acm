#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
g++ -std=c++11 -o k window-on-the-wall.cpp
*/

int main() {
    int w, h, d;
    int x, y;
    cin >> w >> h >> d;
    x = w - 2*d;
    y = h - 2*d;
    if(x < 0 || y < 0)
        cout << 0 << endl;
    else
        cout << x*y << endl;
    return 0;
}
