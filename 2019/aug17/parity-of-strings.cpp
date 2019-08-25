#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

/*
g++ -std=c++11 -o k parity-of-strings.cpp

input
output

coachessoaehwwwwww
0

coachesarefun
2

coachesc
1
*/

int main() {
    map<char, int> r;
    string in;
    bool e = true;
    bool o = true;
    cin >> in;
    for(char c : in)
        r[c] += 1;

    for(auto const& x : r) {
        if(x.second % 2 == 0) o = false;
        else e = false;
    }
    if((o && e) || (!o && !e))
        cout << 2 << endl;
    else if(e) cout << 0 << endl;
    else cout << 1 << endl;

    return 0;
}

