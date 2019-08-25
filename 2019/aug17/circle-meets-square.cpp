#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
g++ -std=c++11 -o k circle-meets-square.cpp

0 0 5
2 3 1
2

0 0 5
5 0 6
1

0 5 4
-1 -1 1
0

*/

bool circle_center_in_square(int x, int y, int r, 
        int tx, int ty, int s) {
    return tx < x && x < (tx + s) && ty < y && y < (ty + s);
}

bool sqr_vtx_in_circle(int x, int y, int r, 
        int tx, int ty, int s) {
    return sqrt(pow(tx - x, 2) + pow(ty - y, 2)) < r ||
        sqrt(pow(tx + s - x, 2) + pow(ty - y, 2)) < r ||
        sqrt(pow(tx - x, 2) + pow(ty + s - y, 2)) < r ||
        sqrt(pow(tx + s - x, 2) + pow(ty + s - y, 2)) < r;
}

bool height_within(int x, int y, int r, 
        int tx, int ty, int s) {
    if(tx <= x && x <= (tx + s) && (abs(ty - y) < r || abs(ty + s - y) < r)) {
        return true;
    }
    if(ty <= y && y <= (ty + s) && (abs(tx - x) < r || abs(tx + s - x) < r)) {
        return true;
    }
    return false;
}

bool sqr_vtx_at_circle(int x, int y, int r, 
        int tx, int ty, int s) {
    return sqrt(pow(tx - x, 2) + pow(ty - y, 2)) == r ||
        sqrt(pow(tx + s - x, 2) + pow(ty - y, 2)) == r ||
        sqrt(pow(tx - x, 2) + pow(ty + s - y, 2)) == r ||
        sqrt(pow(tx + s - x, 2) + pow(ty + s - y, 2)) == r;
}

bool height_at(int x, int y, int r, 
        int tx, int ty, int s) {
    if(tx <= x && x <= (tx + s) && (abs(ty - y) == r || abs(ty + s - y) == r)) {
        return true;
    }
    if(ty <= y && y <= (ty + s) && (abs(tx - x) == r || abs(tx + s - x) == r)) {
        return true;
    }
    return false;
}

int main() {
    int x,y,r;
    int tx,ty,s;
    cin >> x >> y >> r;
    cin >> tx >> ty >> s;

    if(circle_center_in_square(x, y, r, tx, ty, s) ||
            sqr_vtx_in_circle(x, y, r, tx, ty, s) ||
            height_within(x, y, r, tx, ty, s)) {
        cout << 2 << endl;
    } else if(height_at(x, y, r, tx, ty, s) || 
            sqr_vtx_at_circle(x, y, r, tx, ty, s)) {
        cout << 1 << endl;

    } else {
        cout << 0 << endl;
    }
    return 0;
}


