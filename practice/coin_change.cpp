#include<iostream>
#include<vector>
#include<climits>
using namespace std;

/**
g++ -std=c++11 coin_change.cpp -o k

5
1 5 10 25 100
75
o: 3

4
1 3 9 10
15
o: 3

3
7 11 13
1
o: -1

3
7 11 13
29
o: 3
*/
int main() {
    int n, t, acc;
    cin >> n;
    vector<int> coins(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    cin >> t;
    // DP on subtotal
    vector<int> subtotal(t + 1, INT_MAX);
    subtotal[0] = 0;
    for(int i = 1; i <= t; i++) {
        // accumulator to get the smallest # of coins
        // needed to pay (i - coin) amount for every
        // coin in coins
        acc = INT_MAX;
        for(int coin : coins) {
            if(i - coin >= 0 && subtotal[i - coin] < acc) {
                acc = subtotal[i - coin] + 1;
            }
        }
        subtotal[i] = acc;
    }
    if(subtotal[t] == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << subtotal[t] << endl;
    }

    return 0;
}
