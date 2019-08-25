#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
 
// Binary search (note boundaries in the caller)
int CeilIndex(std::vector<int> &v, int l, int r, int key) {
    while (r-l > 1) {
    int m = l + (r-l)/2;
    if (v[m] >= key)
        r = m;
    else
        l = m;
    }
 
    return r;
}
 
int LongestIncreasingSubsequenceLength(std::vector<int> &v) {
    if (v.size() == 0)
        return 0;
 
    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
 
    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < tail[0])
            // new smallest value
            tail[0] = v[i];
        else if (v[i] > tail[length-1])
            // v[i] extends largest subsequence
            tail[length++] = v[i];
        else
            // v[i] will become end candidate of an existing subsequence or
            // Throw away larger elements in all LIS, to make room for upcoming grater elements than v[i]
            // (and also, v[i] would have already appeared in one of LIS, identify the location and replace it)
            tail[CeilIndex(tail, -1, length-1, v[i])] = v[i];
    }
 
    return length;
}
 
/* Example of usage: */

int main() {
  int numChefs = 1;
  vector<int> yr1_skill;
  vector<int> yr2_skill;
  vector<int> yr_skill_chg;

  cin >> numChefs;
  if(numChefs < 1) return 0;
  // int yr_skill_chg[numChefs];
  yr1_skill.reserve(numChefs);
  yr2_skill.reserve(numChefs);
  yr_skill_chg.reserve(numChefs);

  for(int i = 0; i < numChefs; i++)
      cin >> yr1_skill[i];
  for(int i = 0; i < numChefs; i++)
      cin >> yr2_skill[i];

  //Chef chefs[numChefs];

  int yr_skill_chg_arr[numChefs];

  for(int i = 0; i < numChefs; i++) {
    yr_skill_chg_arr[yr1_skill[i] - 1] = yr2_skill[i];
    // array          
  }

  for(int i = 0; i < numChefs; i++) {
    yr_skill_chg.push_back(yr_skill_chg_arr[i]);
  }

  // yr_skill_chg.shrink_to_fit();

  /*for (size_t i = 0; i < numChefs; i++)
    cout << yr_skill_chg_arr[i] << " ";
  cout << endl;*/

  cout << LongestIncreasingSubsequenceLength(yr_skill_chg) << endl;
 
  return 0;
}

/*

g++ -std=c++11 -o lis_chefs lis_chefs.cpp
4
2 3 1 4
3 2 1 4

sol 3

3 4 1 2
^
2 3 1 4
3 2 1 4
v
1 2 3 4

*/