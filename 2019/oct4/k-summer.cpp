#include<iostream>
#include<string>
#include<unordered_set>
using namespace std;

/**
g++ -std=c++11 k-summer.cpp -o k
*/
int main() {
    unordered_set<char> s = unordered_set<char>(); // charaters visited at each i
    //unordered_set<char> s; // charaters visited at each i
    string in;
    cin >> in;
    int count = 0;
    for(int i = 0; i < in.size(); i++) {
        s = unordered_set<char>();
        for(int j = i + 1; j < in.size(); j++) {
            if(in[i] == in[j])
                break;
            else {
                if(s.count(in[j]) > 0) {
                    // don't count this one
                } else {
                    count++;
                    s.insert(in[j]);
                    // print the good itinerary
                    // for(int k = i; k <= j; k++) {
                    //     printf("%c", in[k]);
                    // }
                    // cout << endl;
                }
            }
        }
    }
    
    cout << count << endl;
    return 0;
}

