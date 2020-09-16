#include <bits/stdc++.h>
using namespace std;

typedef long long int lld;
//lld MAX = numeric_limits<int>::max();
typedef double dbl;
typedef pair<dbl, dbl> point;
dbl MAX = numeric_limits<dbl>::max();

void debug() { cout << "DEBUG" << endl; }
template<class T>
void print(T msg) { cout << msg << endl; }
template<class S, class T>
void print(S m1, T m2) { cout << m1 << " " << m2 << endl; }
template<class S, class T, class U>
void print(S m1, T m2, U m3) { cout << m1 << " " << m2 << " " << m3 << endl; }
template<class S, class T, class U, class V>
void print(S m1, T m2, U m3, V m4) { cout << m1 << " " << m2 << " " << m3 << " " << m4 << endl; }
template<class T>
void prVector(vector<T> v) {
    for(T i : v) cout << i << " ";
    cout << endl;
}

/*
g++ -std=c++11 k-kitchen.cpp -o k
runtime error on test 1

python count size
from sympy.functions.combinatorial.factorials import binomial
a = 0
for i in range(17):
    a += binomial(18, i) * binomial(18 - i, 2)
// a == 10,027,008

3 4
2
1 1
2 3
2 1
o: 5.6055512754639896

3 4
3
3 1
1 2
1 4
2 0
o: 5.6502815398728847

3 2
1
1 2
1 1
o: 1

3 7
4
1 1
1 3
2 5
1 6
2 0
o: 12.010469622751655

3 8
6
1 1
2 1
1 4
1 5
1 7
2 7
2 3
o: 16.14218233270955

*/

dbl min_distance(point& x1, point& x2) {
    return sqrt(pow(x2.first - x1.first, 2.0) + pow(x2.second - x1.second, 2.0));
}

dbl min_edge(dbl w, dbl l, point& x1) {
    return min (
        min(x1.first, w - x1.first),
        min(x1.second, l - x1.second)
    );
}

dbl min_dispose(dbl w, dbl l, point& x1, point& x2) {
    // left dispose
    dbl left = sqrt(pow(x2.first + x1.first, 2.0) + pow(x2.second - x1.second, 2.0));
    // right dispose
    dbl right = sqrt(pow(w - x2.first + w - x1.first, 2.0) + pow(x2.second - x1.second, 2.0));
    // top dispose
    dbl top = sqrt(pow(x2.first - x1.first, 2.0) + pow(x2.second + x1.second, 2.0));
    // bottom dispose
    dbl bottom = sqrt(pow(x2.first - x1.first, 2.0) + pow(l - x2.second + l - x1.second, 2.0));
    return min(min(min(left, right), top), bottom);
}

int main() {
    //freopen("kitchen.in", "r", stdin);
    //freopen("kitchen.out", "w", stdout);

    map<lld, map<lld, dbl>> t[2] = {
        map<lld, map<lld, dbl>>(), map<lld, map<lld, dbl>>() };
    vector<int> v1;
    vector<bool> v2;
    vector<int> v3;
    dbl w, l, z1, z2, xr, yr, o;
    point pr;
    int n, s, acc, i, j, k, ii, jj; s = 0;
    lld a, b, c;
    cin >> w >> l;
    cin >> n;
    vector<point> points(n);
    for(i = 0; i < n; i++) {
        // get position of each bottle
        cin >> z1 >> z2;
        points[i] = point(z1, z2);
    }
    // get robot initial position
    cin >> xr >> yr;
    pr = point(xr, yr);

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            t[s][(1LL<<i) + (1LL<<j)][1LL] = min_dispose(w, l, points[i], points[j]);
            //print("|X| = 0", i, j, t[s][(1LL<<i) + (1LL<<j)][1LL]);
        }
    }

    for(i = 1; i <= n - 2; i++) {
        // for each middle bottle set size |X| == i
        s = (s + 1) % 2;
        t[s] = map<lld, map<lld, dbl>>();
        for(j = 0; j < n - 1; j++) {
            for(k = j + 1; k < n; k++) {
                // make indexes (j, k) refer to endpoint bottles
                
                // make rest indexes not j, k refer to possible between bottles
                v1 = vector<int>();
                for(ii = 0; ii < n; ii++) {
                    if(ii != j && ii != k) v1.push_back(ii);
                }

                // produce index combinations of i between bottles by taking from
                // i.e. produce combinations i ints in v1
                a = (1LL<<j) + (1LL<<k); // first hash of endpoint bottle indexes
                v2 = vector<bool>(n - 2);
                fill(v2.begin(), v2.begin() + i, true);
                do {
                    b = 1LL; // hash of middle bottle indexes
                    v3 = vector<int>();
                    for(ii = 0; ii < n; ii++) {
                        if(v2[ii]) { // will be true for i times
                            b += 1LL<<v1[ii];
                            v3.push_back(v1[ii]);
                        }
                    }
                    t[s][a][b] = MAX;
                    for(ii = 0; ii < i; ii++) {
                        // recursion steps set second last bottle ii
                        c = 1LL; // hash of last middle bottle indexes
                        for(jj = 0; jj < i; jj++) {
                            if(jj != ii) c += 1LL<<v3[jj];
                        }
                        //print("test |X| = ", i - 1, j, v3[ii]);
                        //print("test dispose", v3[ii], k, min_dispose(w, l, points[v3[ii]], points[k]));
                        t[s][a][b] = min(
                            t[s][a][b],
                            t[(s + 1) % 2][(1LL<<j) + (1LL<<v3[ii])][c]
                                + min_dispose(w, l, points[v3[ii]], points[k])
                        );
                    }
                    //print("|X| =", i, j, k);
                    //print(t[s][a][b]);
                } while(prev_permutation(v2.begin(), v2.end()));
            }
        }
    }

    if(n == 1) {
        o = min_distance(pr, points[0]) + min_edge(w, l, points[0]);
        cout << setprecision(numeric_limits<dbl>::max_digits10) << o << endl;
        return 0;
    }

    o = MAX;
    for(j = 0; j < n - 1; j++) {
        for(k = j + 1; k < n; k++) {
            b = 1; // hash of middle bottle indexes
            for(ii = 0; ii < n; ii++) {
                if(ii != j && ii != k) b += 1LL<<ii;
            }
            o = min(
                o,
                min(
                    t[s][(1LL<<j) + (1LL<<k)][b] + min_distance(pr, points[j]) + min_edge(w, l, points[k]),
                    t[s][(1LL<<j) + (1LL<<k)][b] + min_distance(pr, points[k]) + min_edge(w, l, points[l])
                )
            );
        }
    }
    cout << setprecision(numeric_limits<dbl>::max_digits10) << o << endl;

    return 0;
}

