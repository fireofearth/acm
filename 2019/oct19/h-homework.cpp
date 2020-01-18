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

struct Assignment {
    int id;
    int s;
    int t;
};

struct SortByT {
    bool operator()(const Assignment *lhs, 
                    const Assignment *rhs) const {
        return lhs->t > rhs->t;
    }
};

struct SortByS {
    bool operator()(const Assignment *lhs, 
                    const Assignment *rhs) const {
        return lhs->s > rhs->s;
    }
};

typedef priority_queue<Assignment *, vector<Assignment *>, SortByT> pqt;
typedef priority_queue<Assignment *, vector<Assignment *>, SortByS> pqs;

/*
g++ -std=c++11 h-homework.cpp -o k
does not work

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
*/
int main() {
    int n; // # total asgmts
    int m; // # asgmts from mathematics
    //int o; // # asgmts from informatics
    int count, d;
    int s, t;
    pqt pq_t;
    pqs pq_math, pq_info;
    queue<Assignment *> q;
    queue<Assignment *> q_math, q_info;
    Assignment *a, *a_math, *a_info;

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> s >> t;
        a = new Assignment{i + 1, s, t};
        pq_t.push(a); // use this to solve for max
        if(i < m) pq_math.push(a); // use this to solve for min
        else pq_info.push(a);
    }

    // solve for max
    count = 0; d = 1;
    while(!pq_t.empty()) {
        a = pq_t.top(); pq_t.pop();
        while(!pq_t.empty() && (a->t < d || d < a->s)) {
            if(d < a->s) q.push(a);
            // else if a->t < d we simply get rid of it
            a = pq_t.top();; pq_t.pop();
        }


        if(a->s <= d && d <= a->t) count++;
        else if(d < a->s) q.push(a);

        while(!q.empty()) {
            pq_t.push(q.front()); q.pop();
        }
        d++;
    }

    cout << count << endl;

    // solve for min
    count = 0; d = 1;
    while(!pq_math.empty() || !pq_info.empty()) {
        if(pq_math.empty()) break;
        if(pq_info.empty()) break;
        
        // otherwise both are not empty
        a_math = pq_math.top(); pq_math.pop();
        // we want to get d <= a_math->t, throw others away
        while(!pq_math.empty() && a_math->t < d) {
            a_math = pq_math.top(); pq_math.pop();
        }

        a_info = pq_info.top(); pq_info.pop();
        // we want to get d <= a_info->t
        while(!pq_info.empty() && a_info->t < d) {
            a_info = pq_info.top(); pq_info.pop();
        }
        
        if((a_math->s <= d && d <= a_math->t) && (a_info->s <= d && d <= a_info->t)) {
            // assigment must be done
            count++;
            if(a_math->t < a_info->t) {
                q_math.push(a_math);
            } else {
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

