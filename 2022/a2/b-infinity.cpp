#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

template<typename T>
void printv(vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i < v.size() - 1)
            cout << " ";
    }
    cout << endl;
}

/*
 * array has indices over [beg, end).
 * beg < end
 */
void subproblem(
    vector<vector<vector<int>>> &mpile,
    vector<vector<int>> &mheight,
    vector<vector<bool>> &visited,
    int beg, int end
) {
    int len = end - beg;
    if(visited[len][beg]) return;

    // compute subproblem
    int i, j;
    int middle;
    visited[len][beg] = true;
    int best_height = 0;
    vector<int> best_pile;
    int height = 0;
    vector<int> pile;
    for(i = beg + 1; i < end; i++) {
        //printf("in loop: %d %d %d\n", beg, i, end);
        // break array into subarrays with indices [beg, i), [i, end)
        subproblem(mpile, mheight, visited, beg, i);
        subproblem(mpile, mheight, visited, i, end);
        vector<int> &lpile = mpile[i - beg][beg];
        vector<int> &rpile = mpile[end - i][i];
        j = lpile.size();
        height = max(mheight[i - beg][beg], mheight[end - i][i]);
        if(lpile[lpile.size() - 1] == rpile[0]) {
            // combine 2 piles
            middle = lpile[lpile.size() - 1] + rpile[0];
            height = max(height, middle);
            pile = vector<int>(lpile.begin(), lpile.end() - 1);
            pile.push_back(middle);
            pile.insert(pile.end(), rpile.begin() + 1, rpile.end());

        } else if(lpile.size() > 1 && lpile[lpile.size() - 2] == rpile[0]) {
            // combine 2 piles from left, 1 pile from right
            middle = lpile[lpile.size() - 2] + lpile[lpile.size() - 1] + rpile[0];
            height = max(height, middle);
            pile = vector<int>(lpile.begin(), lpile.end() - 2);
            pile.push_back(middle);
            pile.insert(pile.end(), rpile.begin() + 1, rpile.end());

        } else if(rpile.size() > 2 && lpile[lpile.size() - 1] == rpile[1]) {
            // combine 1 pile from left, 2 piles from right
            middle = lpile[lpile.size() - 1] + rpile[0] + rpile[1];
            height = max(height, middle);
            pile = vector<int>(lpile.begin(), lpile.end() - 1);
            pile.push_back(middle);
            pile.insert(pile.end(), rpile.begin() + 2, rpile.end());

        } else {
            // don't combine anything
            pile = vector<int>(lpile);
            pile.insert(pile.end(), rpile.begin(), rpile.end());
        }
        //printv(pile);
        if(height > best_height) {
            best_height = height;
            best_pile = pile;
        }
    }
    mheight[len][beg] = best_height;
    mpile[len][beg] = best_pile;
    //printf("at: [%d, %d) %d \n", beg, end, len);
    //cout << mheight[len][beg] << ": ";
    //printv(mpile[len][beg]);
}

/*
DP on subarrays
g++ -std=c++11 b-infinity.cpp -o k
*/
int test() {
    int i, j, k;
    int n; // number of piles
    cin >> n;
    vector<int> a(n); // piles
    for(i = 0; i < n; i++) {
        cin >> a[i];
    }

    // using 2D DP
    // rows is size of chunks of consecutive piles in a
    // column is starting index of chunk
    vector<vector<vector<int>>> mpile(n + 1);
    vector<vector<int>> mheight(n + 1);
    vector<vector<bool>> visited(n + 1);
    for(i = 1; i <= n; i++) {
        mpile[i] = vector<vector<int>>(n - i + 1);
        mheight[i] = vector<int>(n - i + 1);
        visited[i] = vector<bool>(n - i + 1);
    }

    // chunks of size 1
    for(i = 0; i < n; i++) {
        // chunk of size 1 has size equal to the assoc. pile
        mpile[1][i] = {a[i]};
        mheight[1][i] = a[i];
        visited[1][i] = true;
    }

    subproblem(mpile, mheight, visited, 0, n);
    return mheight[n][0];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int i, T;
    cin >> T;
    vector<int> ans(T);
    for(i = 0; i < T; i++)
        ans[i] = test();
    for(i = 0; i < T; i++)
        cout << ans[i] << endl;
}

