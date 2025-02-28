#include <bits/stdc++.h>
using namespace std;

/*
https://open.kattis.com/problems/jollyjumpers
g++ -O2 -std=gnu++23 jollyjumpers.cpp -o k
./k < tests/jollyjumpers-1.in
*/
int main () {
    std::vector<int> els;
    els.reserve(3000);

    std::vector<bool> has;
    has.reserve(3000);

    std::vector<bool> ans;
    ans.reserve(100);
    int n, k;
    while (scanf("%d", &n) != EOF) {
        els = {};
        for (int i = 0; i < n; i++) {
            std::cin >> k;
            els.push_back(k);
        }

        if (n == 1) {
            ans.push_back(true);
            continue;
        }

        has.assign(n - 1, false);
        bool is_oob = false;
        for (int i = 0; i < n - 1; i++) {
            int diff = std::abs(els[i+1] - els[i]);
            if (diff < 1 || n <= diff) {
                is_oob = true;
                break;
            }

            has[diff-1] = true;
        }

        if (is_oob) {
            ans.push_back(false);
            continue;
        }

        bool is_missing = false;
        for (bool is : has) {
            if (!is) {
                is_missing = true;
                break;
            }
        }

        if (is_missing) {
            ans.push_back(false);
            continue;
        }
        
        ans.push_back(true);
    }

    for (bool is : ans) {
        if (is) {
            std::cout << "Jolly\n";
        } else {
            std::cout << "Not jolly\n";
        }
    }
    return 0;
}
