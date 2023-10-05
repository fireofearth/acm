#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long int lld;
lld MAX = numeric_limits<lld>::max();

// nums are guaranteed to be sorted
vector<int> twoSumI(vector<int>& nums, int target) {
    int i = 0;
    int j = nums.size() - 1;
    while (i < j) {
        if (nums[i] + nums[j] > target) {
            j--;
        } else if (nums[i] + nums[j] < target) {
            i++;
        } else {
            return {i, j};
        }
    }
    return {};
}

struct less_than_pair
{
    inline bool operator() (const pii& a, const pii& b) {
        return (a.first < b.first);
    }
};

// nums are arbitrary
vector<int> twoSumII(vector<int>& nums, int target) {
    vector<pii> pnums;
    pnums.reserve(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        pnums.push_back(make_pair(nums[i], i));
    }
    std::sort(pnums.begin(), pnums.end(), less_than_pair());

    int i = 0;
    int j = pnums.size() - 1;
    while (i < j) {
        if (pnums[i].first + pnums[j].first > target) {
            j--;
        } else if (pnums[i].first + pnums[j].first < target) {
            i++;
        } else {
            if (pnums[j].second > pnums[i].second) {
                return {pnums[i].second, pnums[j].second};
            } else {
                return {pnums[j].second, pnums[i].second};
            }
        }
    }
    return {};
}

string tostring(vector<int> o) {
    stringstream ss;
    for (int i = 0; i < o.size(); i++) {
        ss << o[i];
        if (i < o.size() - 1)
            ss << " ";
    }
    return ss.str();
}

void __trial_1() {
    vector<int> i = {2, 3, 5};
    int t = 7;
    vector<int> o = twoSumI(i, t);
}

void __trial_2() {
    vector<int> i = {2, 4, 5, 7, 10};
    int t = 9;
    vector<int> o = twoSumI(i, t);
}

void __trial_3() {
    vector<int> i = {4, 2, 10, 7, 5};
    int t = 9;
    vector<int> o = twoSumII(i, t);
    cout << "input " << tostring(i) << endl;
    cout << "target " << t << endl;
    cout << "output " << tostring(o) << endl;
}

// g++ -std=c++14 two_sum_i_ii.cpp -o k
int main() {
    // __trial_1();
    // __trial_2();
    __trial_3();
    return 0;
}

