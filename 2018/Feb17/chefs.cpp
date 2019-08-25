#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

/*enum Change { INC   = 1, SAME = 0, DEC = -1 };

struct Chef {
  int yr1_skill;
  int yr2_skill;
  Change change;
}*/

class DisjointSets {
  public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
  private:
    vector<int> values;
};

void DisjointSets::addelements(int num)
{
    // add 'num' values of -1
    values.reserve(values.size() + num);
    for (int i = 0; i < num; i++)
        values.push_back(-1);
}

int DisjointSets::find(int elem)
{
    if (values[elem] < 0) // if a root, return
        return elem;
    else // otherwise find the root and path compress
        return values[elem] = find(values[elem]);
}

int DisjointSets::size(int elem)
{
    return -values[find(elem)];
}

void DisjointSets::setunion(int a, int b)
{
    // Find roots
    a = find(a);
    b = find(b);
    // Check for self assignment
    if (a != b) {
        // union by size
        if (values[a] <= values[b]) {
            values[a] += values[b];
            values[b] = a;
        } else {
            values[b] += values[a];
            values[a] = b;
        }
    }
}

/*


clang -std=c++11 -o chefs chefs.cpp
4
2 3 1 4
3 2 1 4

*/
int main(/*int argc, char* argv[]*/) {
  int numChefs = 1;
  vector<int> yr1_skill;
  vector<int> yr2_skill;

  cin >> numChefs;
  if(numChefs < 1) return 0;
  int yr_skill_chg[numChefs];
  yr1_skill.reserve(numChefs);
  yr2_skill.reserve(numChefs);

  for(int i = 0; i < numChefs; i++)
      cin >> yr1_skill[i];
  for(int i = 0; i < numChefs; i++)
      cin >> yr2_skill[i];

  //Chef chefs[numChefs];

  for(int i = 0; i < numChefs; i++) {
    yr_skill_chg[yr1_skill[i]] = yr2_skill[i];
  }

  /*for(int i = 0; i < numChefs; i++) {
    chefs[i].yr1_skill = yr1_skill[i];
    chefs[i].yr2_skill = yr2_skill[i];
  }*/

  // scan
  DisjointSets dset = DisjointSets();
  for(int i = 0; i < numChefs; i++) {
    dset.addelements(yr1_skill[i]);
  }

  for(int i = 0; i < numChefs; i++) {
    dset.setunion(yr1_skill[i], yr2_skill[i]);
  }

  set<int> groups;
  // for(auto skill: yr1_skill)
  // for(auto it = yr1_skill.begin(); it < yr1_skill.end(); ++it) {
  for(int i = 1; i <= numChefs; i++) {
    // cout << "DEBUG: " << dset.find(i) << endl;
    int find = dset.find(i);
    if(find != i) {
      groups.emplace(dset.find(i));
    }
  }

  int nbr_chefs_chg_ranks = 0;
  for(auto it = groups.begin(); it != groups.end(); ++it) {
    if(*it > yr_skill_chg[*it])
      nbr_chefs_chg_ranks = nbr_chefs_chg_ranks + (*it - yr_skill_chg[*it]);
    else
      nbr_chefs_chg_ranks = nbr_chefs_chg_ranks + (yr_skill_chg[*it] - *it);
  }
  cout << (numChefs - nbr_chefs_chg_ranks) << endl;

  return 0;
}

/*


clang -std=c++11 -o chefs chefs.cpp
4
2 3 1 4
3 2 1 4

sol: 3

*/