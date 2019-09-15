#include <iostream>
#include <unordered_map>
using namespace std;

typedef unsigned long long int mlong;

/*

g++ -std=c++11 toy-soldiers.cpp -o k
 */

int main() {

    int n; // number of soldiers
    cin >> n;
    int a[n]; // colors the soldiers painted
    // key - paint #
    // value - # soldiers painted with (paint #)
    unordered_map<int, int> paint_cnt;
    bool is_reached = false;
    int same_clr = 0;

    for(int i = 0; i < n; i++) {
    }
    return 0;
}

