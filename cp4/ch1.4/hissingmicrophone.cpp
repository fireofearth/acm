#include <bits/stdc++.h>
using namespace std;

/*
kattis
g++ -O2 -std=gnu++23 hissingmicrophone.cpp -o k
*/
int main () {
    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == 's' && s[i+1] == 's') {
            std::cout << "hiss\n";
            return 0;
        }
    }
    std::cout << "no hiss\n";
    return 0;
}

