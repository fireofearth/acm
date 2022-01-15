#include<iostream>
#include<vector>
#include<stack>
#include<utility>
using namespace std;

typedef pair<int, int> pii;

int digit_sum(int a) {
    int sum = 0;
    while(a > 0) {
        sum += a % 10;
        a = a / 10;
    }
    return sum;
}

int digit_sum_2(int a, int b) {
    return digit_sum(a) + digit_sum(b);
}

/**
g++ -std=c++11 robot_move.cpp -o k
not sure how to test this effectively
*/
int main() {
    int n, m, k;
    int i, j;
    cin >> m >> n >> k;
    vector<vector<bool>> visited(m);
    for(int i = 0; i < m; i++) {
        visited[i] = vector<bool>(n, false);
    }

    int count = 1;
    pii curr = make_pair(0, 0);
    stack<pii> s;
    s.push(curr);
    while(true) {
        if(s.empty()) break;
        curr = s.top();
        // row
        i = curr.first;
        // col
        j = curr.second;
        if(i + 1 < m && !visited[i + 1][j]
                && digit_sum_2(i + 1, j) <= k) {
            // move down
            visited[i + 1][j] = true;
            curr = make_pair(i + 1, j);
            s.push(curr);
            count++;
        } else if(j + 1 < n && !visited[i][j + 1]
                && digit_sum_2(i, j+ 1) <= k) {
            // move right
            visited[i][j + 1] = true;
            curr = make_pair(i, j + 1);
            s.push(curr);
            count++;
        } else if(i - 1 > 0 && !visited[i - 1][j]
                && digit_sum_2(j - 1, j) <= k) {
            // move up
            visited[i - 1][j] = true;
            curr = make_pair(i - 1, j);
            s.push(curr);
            count++;
        } else if(j - 1 > 0 && !visited[i][j - 1]
                && digit_sum_2(i, j - 1) <= k) {
            // move left
            visited[i][j - 1] = true;
            curr = make_pair(i, j - 1);
            s.push(curr);
            count++;
        } else {
            s.pop();
        }
    }

    cout << count << endl;
    
    return 0;
}
