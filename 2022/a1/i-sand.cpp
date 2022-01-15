#include <bits/stdc++.h>
using namespace std;

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

bool DEBUG = false;

vector<pii> clause_to_edges(
    string clause,
    map<string, int> &name_to_idx
) {
    int i;
    bool neg1 = false;
    bool neg2 = false;
    int beg1, end1, len1;
    int beg2, end2, len2;
    int var1, var2;
    char op;
    // find start of first variable
    for(i = 0; i < clause.length(); i++) {
        if(clause[i] >= 'a' && clause[i] <= 'z') {
            beg1 = i; break;
        }
        if(clause[i] == '-')  neg1 = true;
    }
    // find end of first variable
    for(i = beg1; i < clause.length(); i++) {
        if(clause[i] == ' ') {
            end1 = i; break;
        }
    }
    len1 = end1 - beg1;
    // find the operation used in clause
    op = clause[end1 + 1];
    // find start of second variable
    for(i = end1; i < clause.length(); i++) {
        if(clause[i] >= 'a' && clause[i] <= 'z') {
            beg2 = i; break;
        }
        if(clause[i] == '-')  neg2 = true;
    }
    // find end of second variable
    for(i = beg2; i < clause.length(); i++) {
        if(clause[i] == ')') {
            end2 = i; break;
        }
    }
    len2 = end2 - beg2;
    // get var from strs
    var1 = 2*name_to_idx[clause.substr(beg1, len1)];
    var2 = 2*name_to_idx[clause.substr(beg2, len2)];

    if(DEBUG) {
        cout << "BEGIN(" << endl;
        cout << clause.substr(beg1, len1) << endl;
        cout << op << endl;
        cout << clause.substr(beg2, len2) << endl;
        cout << clause << endl;
        printf("at: %d %s %c %d %s\n",
            neg1, clause.substr(beg1, len1).c_str(),
            op, neg2, clause.substr(beg2, len2).c_str()
        );
        printf("to: %d %d\n", var1, var2);
        cout << ")END" << endl;
    }

    if(op == '&') {
        // (a & b) = (~a => a) & (~b => b)
        return {{var1^!neg1, var1^neg1}, {var2^!neg2, var2^neg2}};
    } else if(op == '|') {
        // (a | b) = (~a => b) & (~b => a)
        return {{var1^!neg1, var2^neg2}, {var2^!neg2, var1^neg1}};
    } else { // op == '='
        // (a => b) = (~a | b) = (a => b) & (~b => ~a)
        return {{var1^neg1, var2^neg2}, {var2^!neg2, var1^!neg1}};
    }
}

void test(vector<pair<int, vector<string>>> &ans) {
    int N; // variables
    int M; // clauses
    int i, j, k;
    int u, v;

    cin >> N;
    vector<string> idx_to_name(N);
    map<string, int> name_to_idx;
    for(i = 0; i < N; i++) {
        cin >> idx_to_name[i];
        name_to_idx[idx_to_name[i]] = i;
    }

    // construct 2SAT graph
    int n = 2*N; // nodes
    int m = 0; // edges
    vector<vector<int>> adj(n);
    cin >> M;
    // clear line before using getline to read entire line to string
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    vector<string> clauses(M);
    for(i = 0; i < M; i++) {
        getline(cin, clauses[i]);
    }
    for(i = 0; i < M; i++) {
         vector<pii> clause_edges = clause_to_edges(clauses[i], name_to_idx);
         for(pii edge : clause_edges) {
            adj[get<0>(edge)].push_back(get<1>(edge));
            m++;
         }
    }

    // Find SCC using iterative DFS
    stack<int> s; // for recusing DFS iteratively
    stack<int> t; // for backtrack DFS iteratively
    stack<int> z; // for adding to SCC
    vector<int> indices(n, -1); // index of discovery
    vector<int> lowests(n, -1); // lowest index observed
    vector<int> comp(n, -1); // component of node
    int index = 0; // index to set each node
    int compi = 0; // component to set each node
    for(i = 0; i < n; i++) {
        if(indices[i] != -1) continue;
        s.push(i);
        while(!s.empty()) {
            // get next node
            u = s.top(); s.pop();
            if(indices[u] == -1) {
                lowests[u] = indices[u] = index; index++;
                z.push(u);

                // recurse DFS
                for(int v : adj[u]) {
                    s.push(v);
                    t.push(u);
                }
                if(t.empty() || u != t.top()) t.push(u);
                if(adj[u].size() > 0) continue;
            }

            // backtrack DFS
            while(!t.empty()) {
                u = t.top(); t.pop();
                if(!t.empty() && u == t.top()) break;
                for(int v : adj[u])
                    if(comp[v] == -1) {
                        lowests[u] = min(lowests[u], lowests[v]);
                    }
                if(indices[u] <= lowests[u]) {
                    do {
                        v = z.top(); z.pop();
                        comp[v] = compi;
                    } while(u != v);
                    compi++;
                }
            }
        }
    }

    if(DEBUG) {
        cout << "BEGIN(" << endl;
        for(i = 0; i < N; i++) {
            cout << idx_to_name[i] << " " << 2*i << endl;
        }
        printv(comp);
        cout << ")END" << endl;
    }
    
    // Solve 2SAT
    vector<bool> truth(N);
    int norder = 0;
    for(i = 0; i < n; i += 2) {
        if(comp[i] == comp[i^1]) {
            norder = -1;
            break;
        }
        truth[i / 2] = comp[i] < comp[i^1];
    }
    // Solve problem
    vector<string> donuts;
    if(norder != -1)
        for(i = 0; i < N; i++) {
            if(truth[i]) {
                donuts.push_back(idx_to_name[i]);
                norder++;
            }
        }
    ans.emplace_back(norder, donuts);
}

/*
Parse chars and substrings from line.
Convert binary expressions to 2SAT.
Solve using 2SAT and Strongly Connected Components
g++ -std=c++11 i-sand.cpp -o k
*/
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (argc > 1) {
        string arg = argv[1];
        DEBUG = arg == "debug";
    }
    int T, i;
    cin >> T;
    vector<pair<int, vector<string>>> ans;
    ans.reserve(T);
    for(int i = 0; i < T; i++) {
        test(ans);
    }
    for(pair<int, vector<string>> a : ans) {
        cout << get<0>(a) << endl;
        for(string s : get<1>(a))
            cout << s << endl;
    }
    return 0;
}
