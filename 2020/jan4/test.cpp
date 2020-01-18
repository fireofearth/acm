#include <bits/stdc++.h>
using namespace std;

/*
g++ -std=c++11 test.cpp -o k
*/
int main() {
    forward_list<int> f;
    //int i;
    f.push_front(3);
    f.push_front(2);
    f.push_front(1);
    for(int i : f) cout << i << " ";
    cout << endl;

    return 0;
}
