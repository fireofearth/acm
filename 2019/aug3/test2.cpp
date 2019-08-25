#include <iostream>
#include <string>
#include <vector>

using namespace std;

void debug() {
    cout << "DEBUG" << endl;
}

void disp(bool m) {
    cout << (m ? "true" : "false") << endl;
}

void disp(char m) {
    cout << m << endl;
}

void disp(int m) {
    cout << m << endl;
}

void disp(string m) {
    cout << m << endl;
}

/*
g++ -std=c++11 -o k test2.cpp
*/

inline void helper(vector<pair<char, int>> &v) {
    if(v.back().second % 4 == 0)
        v.pop_back();
    else {
        v.back().second = v.back().second % 4;
        if(v.back().second == 3) {
            v.back().second = 1;
            v.back().first  = (v.back().first == 'R' ? 'L' : 'R');
        }
    }
}

bool compress(string &rots) {
    if(rots.length() <= 2) return false;
    vector<pair<char, int>> v;
    v.push_back(pair<char, int>(rots[0], 1));
    for(int ii = 1; ii < rots.length(); ii++) {
        if(v.back().first != rots[ii]) {
            helper(v);
            v.push_back(pair<char, int>(rots[ii], 1));
        } else v.back().second++;
    }
    helper(v);

    // for(int ii = 0; ii < v.size(); ii++)
    //     cout << v[ii].first << v[ii].second << " ";
    // cout << endl;
    
    rots = "";
    int jj;
    for(int ii = 0; ii < v.size(); ii += 2) {
        if(ii == v.size() - 1) {
            for(jj = 0; jj < v[ii].second; jj++)
                rots += v[ii].first;

        } else if(v[ii].first == v[ii + 1].first) {
            for(jj = 0; jj < v[ii].second + v[ii + 1].second; jj++)
                rots += v[ii].first;

        } else { // if(v[ii].first != v[ii + 1].first) {
            if(v[ii].second > v[ii + 1].second)
                rots += v[ii].first;
            else if(v[ii].second < v[ii + 1].second)
                rots += v[ii + 1].first;
        }
    }

    return true;
}

int main() {
    string rots;
    cin >> rots;
    while(compress(rots)) {}
    cout << rots << endl;

    return 0;
}














