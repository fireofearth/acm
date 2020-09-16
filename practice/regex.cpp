#include <bits/stdc++.h>
using namespace std;

typedef string::iterator siter;

bool is_dot(siter p0) {
    return *p0 == '.';
}

bool has_qs(siter p0, string& pat) {
    return (p0 + 1) != pat.end() && *(p0 + 1) == '?';
}

bool has_star(siter p0, string& pat) {
    return (p0 + 1) != pat.end() && *(p0 + 1) == '*';
}

bool _match(string& pat, string& s, siter p0, siter p1) {
    bool at_dot = false;
    char t;

    while(p0 != pat.end() || p1 != s.end()) {
        if(is_dot(p0)) {
            at_dot = true;
            t = *p1;
        }

        if(has_qs(p0, pat)) {
            if(_match(pat, s, p0 + 2, p1))
                return true;
            if(!at_dot && *p0 != *p1)
                return false;
            p0 += 2;
            p1++;
        } else if(has_star(p0, pat)) {
            if(!at_dot)
                t = *p0;
            while(*p1 == t) {
                if(_match(pat, s, p0 + 2, p1))
                    return true;
                p1++;
            }
            p0 += 2;
        } else {
            if(!at_dot && *p0 != *p1)
                return false;
            p0++;
            p1++;
        }
        at_dot = false;
    }

    return p0 == pat.end() && p1 == s.end();
}

bool match(string& pat, string& s) {
    return _match(pat, s, pat.begin(), s.begin());
}

/**

..*a
abaa -> no
aba

g++ -std=c++11 regex.cpp -o k
*/
int main() {
    bool in = false;
    string pat = "";
    string s = "a";
    if(in) {
        //cout << "pattern: ";
        cin >> pat;
        //cout << "string: ";
        cin >> s;
    }
    if(match(pat, s)) {
        cout << s << " matches pattern " << pat << endl;
    } else {
        cout << s << " does not match pattern " << pat << endl;
    }
    return 0;
}

