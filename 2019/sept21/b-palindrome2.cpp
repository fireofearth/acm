#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef unsigned long long int mlong;

/*

g++ -std=c++11 b-palindrome.cpp -o k
1 to 2*10^5 strings
*/

int main() {
    string tin, tout;
    stack<char> s1, s2, s3;
    bool is_p = true;
    bool is_ic;
    cin >> tin;

    int i = 0;
    int j = 0;
    for(; i < tin.size() / 2; i++) {
        s1.push(tin[i]);
        s2.push(tin[i]);
    }

    if(tin.size() % 2 == 1) {
        if(i + 1 < tin.size() && s2.top() == tin[i + 1]) {
            // possibly incomplete palindrome
            s3 = s2;
            j = i + 1;
            is_ic = true;
            for(; j < tin.size(); j++) {
                if(s3.top() != tin[j]) {
                    is_ic = false;
                    break;
                }
                s3.pop();
            }
            if(is_ic) {
                cout << tin;
                while(!s3.empty()) {
                    cout << s3.top();
                    s3.pop();
                }
                cout << endl;
                return 0;
            }
        }
        if(i + 1 < tin.size() && tin[i] == tin[i + 1]) {
            s3 = s2;
            j = i + 2;
            is_ic = true;
            for(; j < tin.size(); j++) {
                if(s3.top() != tin[j]) {
                    is_ic = false;
                    break;
                }
                s3.pop();
            }
            if(is_ic) {
                cout << tin;
                while(!s3.empty()) {
                    cout << s3.top();
                    s3.pop();
                }
                cout << endl;
                return 0;
            }
        }
        s2.push(tin[i]);
        i++;
    }

    for(; i < tin.size(); i++) {
        if(s1.top() != tin[i]) {
            is_p = false;
            if(i + 1 < tin.size() && s2.top() == tin[i + 1]) {
                // possibly incomplete palindrome
                s3 = s2;
                j = i + 1;
                is_ic = true;
                for(; j < tin.size(); j++) {
                    if(s3.top() != tin[j]) {
                        is_ic = false;
                        break;
                    }
                    s3.pop();
                }
                if(is_ic) {
                    cout << tin;
                    while(!s3.empty()) {
                        cout << s3.top();
                        s3.pop();
                    }
                    cout << endl;
                    return 0;
                }
            }
            if(i + 1 < tin.size() && tin[i] == tin[i + 1]) {
                s3 = s2;
                j = i + 2;
                is_ic = true;
                for(; j < tin.size(); j++) {
                    if(s3.top() != tin[j]) {
                        is_ic = false;
                        break;
                    }
                    s3.pop();
                }
                if(is_ic) {
                    cout << tin;
                    while(!s3.empty()) {
                        cout << s3.top();
                        s3.pop();
                    }
                    cout << endl;
                    return 0;
                }
            }
        }
        s1.pop();
        s2.push(tin[i]);
    }

    cout << tin;
    s2.pop(); // shorten palidrome
    if(!is_p) {
        while(!s2.empty()) {
            cout << s2.top();
            s2.pop();
        }
    }
    cout << endl;

    return 0;
}


