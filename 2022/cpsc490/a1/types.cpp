#include <bits/stdc++.h>
using namespace std;

/*
Output from `uname -m` is x86_64
int is -2147483648 ... 2147483647

long is -9223372036854775808 ... 9223372036854775807

long long is -9223372036854775808 ... 9223372036854775807


<https://stackoverflow.com/questions/18971732/what-is-the-difference-between-long-long-long-long-int-and-long-long-i>

g++ -std=c++11 types.cpp -o t
*/
int main() {
    //int _i;
    long long _i;
    cin >> _i;
    cout << _i << endl;
    return 0;
}

