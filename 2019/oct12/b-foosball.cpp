#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <utility>
using namespace std;

void debug() {
    cout << "DEBUG" << endl;
}

typedef pair<int, int> player_pair;

/*
Didn't get this one

g++ -std=c++11 b-foosball.cpp -o k

6
Balaji David Alex Scott Andrew Ravi
WWBWBBWBW

6
Amy Jinu Kasey Sarah Sheetal Julia
BBBBB

10
a b c d e f g h i j
WW

10
a b c d e f g h i j
WWBB

10
a b c d e f g h i j
WBBBW

5
a b c d e
B
o:
b d

5
a b c d e
BW
o:
b d
a e

5
a b c d e
BWW
o:
a e
*/
int main() {
    queue<int> q;
    int n, wo, wd, bo, bd, tmp;
    wo = 0; bo = 1; wd = 2; bd = 3;
    int wa1, wa2, ba1, ba2;
    wa1 = 0; wa2 = 2; ba1 = 1; ba2 = 3;
    player_pair pp;
    set<player_pair> spp;
    vector<player_pair> vpp;
    int k; k = 0; // used to find len of dynasty
    int acc; acc = 1; // acc to track len of longest dynasty
    string outcomes;

    cin >> n;
    string names[n];
    for(int i = 0; i < n; i++) {
        cin >> names[i];
        if(i >= 4) q.push(i);
    }
    cin >> outcomes;

    int i = 0;
    for(; i < outcomes.size(); i++) {
        if(i > 0 && outcomes[i] != outcomes[i - 1]) {
            // change dynasty
            //cout << k << " " << acc << endl;
            if(k >= acc) {
                if(outcomes[i - 1] == 'W') // w dynasty record
                    pp = player_pair(wa1, wa2);
                else // b dynasty recod
                    pp = player_pair(ba1, ba2);

                if(k > acc) {
                    spp = set<player_pair>();
                    vpp = vector<player_pair>();
                }

                if(!spp.count(pp)) {
                    spp.insert(pp);
                    vpp.push_back(pp);
                }
                acc = k;
            }
            k = 1;
        } else {
            // dynasty continued
            k++;
        }
        if(outcomes[i] == 'W') { // w wins
            swap(wo, wd);
            tmp = bd;
            bd = bo;
            q.push(tmp);
            bo = q.front();
            q.pop();
            ba1 = bd;
            ba2 = bo;
        } else { // b wins
            swap(bo, bd);
            tmp = wd;
            wd = wo;
            q.push(tmp);
            wo = q.front();
            q.pop();
            wa1 = wd;
            wa2 = wo;
        }
    }
    
    if(k >= acc) {
        if(outcomes[i - 1] == 'W') // w dynasty record
            pp = player_pair(wa1, wa2);
        else // b dynasty recod
            pp = player_pair(ba1, ba2);

        //cout << k << " " << acc << endl;
        if(k > acc) {
            spp = set<player_pair>();
            vpp = vector<player_pair>();
        }

        if(!spp.count(pp)) {
            spp.insert(pp);
            vpp.push_back(pp);
        }
    }

    for(const player_pair &ppo : vpp)
        cout << names[ppo.first] << " " << names[ppo.second] << endl;

    return 0;
}
