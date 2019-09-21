#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef unsigned long long int mlong;

/*

g++ -std=c++11 b-palindrome.cpp -o k
1 to 2*10^5 strings
*/

void debug() {
    cout << "DEBUG" << endl;
}

bool fill(const string& tin, stack<char> s3, int j) {
    for(; j < tin.size(); j++) {
        if(s3.empty() || s3.top() != tin[j]) {
            return false;
        }
        s3.pop();
    }
    cout << tin;
    while(!s3.empty()) {
        cout << s3.top();
        s3.pop();
    }
    cout << endl;
    return true;
}

int main() {
    string tin, tout;
    stack<char> s1, s2;
    cin >> tin;

    int i = 0;
    int j = 0;
    for(; i < tin.size(); i++) {
        j = i + 1;
        while(j < tin.size() && tin[j] == tin[j - 1]) j++;
        if(fill(tin, s2, j)) return 0;
        // post
        s2.push(tin[i]);
    }

    return 0;
}


