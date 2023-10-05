#include <bits/stdc++.h>
using namespace std;

/*
Given a list of prices over time for a stock
figure out the largest revenue possible to gain
by buying and selling this stock

g++ -std=c++11 buy_sell.cpp -o k
*/
void cases() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int buy = v[0];
    int largest_reward = 0;
    int reward;
    for(int i = 0; i < n; i++) {
        if(buy > v[i]) {
            buy = v[i];
        } else {
            reward = v[i] - buy;
            if(reward > largest_reward) {
                largest_reward = reward;
            }
        }
    }
    cout << largest_reward << endl;
}
int main() {
    int T;
    cin >> T;
    for(int i = 0; i < T; i++) {
        cases();
    }

    return 0;
}
