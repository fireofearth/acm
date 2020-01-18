#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

void debug() {
    cout << "DEBUG" << endl;
}

void debug(int n) {
    cout << "DEBUG " << n << endl;
}

void debug(int n, int m) {
    cout << "DEBUG " << n << " " << m << endl;
}

struct Assignment {
    int id;
    int s;
    int t;
};

struct SortByT {
    bool operator()(const Assignment *lhs, 
                    const Assignment *rhs) const {
        if(lhs->t == rhs->t) return lhs->id > rhs->id;
        else return lhs->t > rhs->t;
    }
};

typedef priority_queue<Assignment *, vector<Assignment *>, SortByT> pqt;

/*
g++ -std=c++11 h-homework.cpp -o k
does not work...
6 3
1 2
1 5
2 3
2 6
4 5
4 6

6 3
1 1
2 3
4 4
1 1
2 4
3 3

4 2
3 4
1 2
1 3
2 4
*/
int main() {
    int n; // # total asgmts
    int m; // # asgmts from mathematics
    //int o; // # asgmts from informatics
    int count, d;
    int s, t;
    pqt pq_math, pq_info;
    pqt pq_math_tmp, pq_info_tmp;
    queue<Assignment *> q_math, q_info;
    Assignment *a, *a_math, *a_info;

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> s >> t;
        a = new Assignment{i + 1, s, t};
        if(i < m) pq_math.push(a);
        else pq_info.push(a);
    }
    pq_math_tmp = pq_math;
    pq_info_tmp = pq_info;

    // solve for max
    count = 0; d = 1;
    while(!pq_math.empty() || !pq_info.empty()) {
        if(pq_math.empty()) {
            a_info = pq_info.top(); pq_info.pop();
            // we want to get d <= a_info->t
            while(!pq_info.empty() && (d < a_info->s || a_info->t < d)) {
                if(d < a_info->s) q_info.push(a_info);
                a_info = pq_info.top(); pq_info.pop();
            }
            if(a_info->s <= d && d <= a_info->t) {
                count++;
            } else if(d <= a_info->t) {
                q_info.push(a_info);
            }
        } else if(pq_info.empty()) {
            a_math = pq_math.top(); pq_math.pop();
            // we want to get d <= a_math->t
            while(!pq_math.empty() && (d < a_math->s || a_math->t < d)) {
                if(d < a_math->s) q_math.push(a_math);
                a_math = pq_math.top(); pq_math.pop();
            }
            if(a_math->s <= d && d <= a_math->t) {
                count++;
            } else if(d <= a_math->t) {
                q_math.push(a_math);
            }
        } else {
            // otherwise both are not empty
            a_math = pq_math.top(); pq_math.pop();
            // we want to get d <= a_math->t, throw others away
            while(!pq_math.empty() && (d < a_math->s || a_math->t < d)) {
                if(d < a_math->s) q_math.push(a_math);
                a_math = pq_math.top(); pq_math.pop();
            }

            a_info = pq_info.top(); pq_info.pop();
            // we want to get d <= a_info->t
            while(!pq_info.empty() && (d < a_info->s || a_info->t < d)) {
                if(d < a_info->s) q_info.push(a_info);
                a_info = pq_info.top(); pq_info.pop();
            }
        
            if((a_math->s <= d && d <= a_math->t) && (a_info->s <= d && d <= a_info->t)) {
                // assigment must be done
                count++;
                if(a_math->t < a_info->t) {
                    q_info.push(a_info);
                } else {
                    q_math.push(a_math);
                }
            } else if(a_math->s <= d && d <= a_math->t) {
                // we do a_math today
                count++;
                if(d <= a_info->t) q_info.push(a_info);
            } else if(a_info->s <= d && d <= a_info->t) {
                // we do a_info today
                count++;
                if(d <= a_math->t) q_math.push(a_math);
            } else {
                if(d <= a_math->t) q_math.push(a_math);
                if(d <= a_info->t) q_info.push(a_info);
            }
        }

        while(!q_math.empty()) {
            pq_math.push(q_math.front()); q_math.pop();
        }
        while(!q_info.empty()) {
            pq_info.push(q_info.front()); q_info.pop();
        }
        d++;
    }

    cout << count << endl;
    pq_math = pq_math_tmp;
    pq_info = pq_info_tmp;

    // solve for min
    count = 0; d = 1;
    while(!pq_math.empty() && !pq_info.empty()) {
        
        // otherwise both are not empty
        a_math = pq_math.top(); pq_math.pop();
        // we want to get d <= a_math->t, throw others away
        while(!pq_math.empty() && (d < a_math->s || a_math->t < d)) {
            if(d < a_math->s) q_math.push(a_math);
            a_math = pq_math.top(); pq_math.pop();
        }

        a_info = pq_info.top(); pq_info.pop();
        // we want to get d <= a_info->t
        while(!pq_info.empty() && (d < a_info->s || a_info->t < d)) {
            if(d < a_info->s) q_info.push(a_info);
            a_info = pq_info.top(); pq_info.pop();
        }
        //cout << "day " << d << endl;
        //debug(a_math->id, a_info->id);
        //cout << "must " << ((a_math->s <= d && d <= a_math->t) && (a_info->s <= d && d <= a_info->t)) << endl;
        
        if((a_math->s <= d && d <= a_math->t) && (a_info->s <= d && d <= a_info->t)) {
            // assigment must be done
            count++;
            if(a_math->t < a_info->t) {
                //debug(a_info->id);
                q_math.push(a_math);
            } else {
                //debug(a_math->id);
                q_info.push(a_info);
            }
        } else if(a_math->s <= d && d <= a_math->t) {
            // we can skip a_math today
            q_math.push(a_math);
            if(d <= a_info->t) q_info.push(a_info);
        } else if(a_info->s <= d && d <= a_info->t) {
            // we can skip a_info today
            q_info.push(a_info);
            if(d <= a_math->t) q_math.push(a_math);
        } else {
            if(d <= a_math->t) q_math.push(a_math);
            if(d <= a_info->t) q_info.push(a_info);
        }

        while(!q_math.empty()) {
            pq_math.push(q_math.front()); q_math.pop();
        }
        while(!q_info.empty()) {
            pq_info.push(q_info.front()); q_info.pop();
        }
        d++;
    }

    cout << count << endl;

    return 0;
}

