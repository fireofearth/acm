#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool is_gate(char in) {
    return (in == '*' || in == '+' || in == '-');
}


bool is_binary(char in) {
    return (in == '*' || in == '+');
}

/**
g++ -std=c++11 a-circuit.cpp -o k
*/
int main() {
    stack<bool> s;
    int n, at_letter, k;
    at_letter = 0; k = 0;
    char in;
    string line;
    cin >> n;
    bool b[n];
    bool o1, o2;
    for(int i = 0; i < n; i++) {
        cin >> in;
        if(in == 'F') b[i] = false;
        else b[i] = true;
    }

    cin.ignore();
    getline(cin, line);

    while(k < line.size()) {
        in = line[k]; k++;
        if(in == ' ' || in == '\n')
            continue;

        if(is_gate(in)) {
            if(is_binary(in)) {
                o1 = s.top(); s.pop();
                o2 = s.top(); s.pop();
                if(in == '*') { // * AND
                    s.push(o1 && o2);
                } else { // + OR
                    s.push(o1 || o2);
                }
            } else { // is singular - NOT
                o1 = s.top(); s.pop();
                s.push(!o1);
            }
        } else { // A B ... Z
            s.push(b[at_letter]);
            at_letter++;
        }
    }
    cout << (s.top() ? 'T' : 'F') << endl;

    return 0;
}
