#include <bits/stdc++.h>
using namespace std;

/*
Example of using priority queue
g++ -std=c++11 pqueue.cpp -o k
*/

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    priority_queue<
        pair<float, int>, // type to store
        vector<pair<float, int>>, // underlyting container
        greater<pair<float, int>> // comparator
    > q;
    q.push({0.0, 1});
    q.push({1.5, 2});
    q.push({0.1, 3});
    q.push({2.1, 4});
    q.push({-0.2, 5});
    q.push({-1.0, 6});
    while(!q.empty()) {
        float curr_val;
        int curr_node;
        tie(curr_val, curr_node) = q.top(); q.pop();
        cout << curr_val << " " << curr_node << endl;
    }
    return 0;
}

