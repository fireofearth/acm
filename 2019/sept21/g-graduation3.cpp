#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;

void debug() { printf("DEBUG\n"); }
void debug(int i) { printf("DEBUG: %d\n", i); }

class Graph {
public:
    Graph(int n) {
        if(n <= 0)
            throw std::invalid_argument( "n must be positive" );
        size = n;
        edges = new bool*[size];
        for(int i = 0; i < n; i++) {
            edges[i] = new bool[size];
            for(int j = 0; j < n; j++)
                edges[i][j] = false;
        }
    }

    /* destructor */
    ~Graph() {
        internal_destructor();
    }

    /* copy constructor */
    Graph(const Graph &g) {
        internal_copy(g);
    }

    /* assignment operator */
    Graph& operator=(const Graph &g) {
        if(this == &g) return *this;
        internal_destructor();
        internal_copy(g);
        return *this;
    }

    int get_size() { return size; }

    /* returns true iff edge has been added successfully */
    bool add_edge(int from, int to) {
        if(edges[from][to])
            return false;
        else {
            edges[from][to] = true;
            return true;
        }
    }

    /* returns true iff edge has been removed successfully */
    bool rem_edge(int from, int to) {
        if(edges[from][to]) {
            edges[from][to] = false;
            return true;
        } else
            return false;
    }

    set<int> outgoing_edges(int vertex) {
        if(vertex < 0 || vertex >= size)
            throw std::invalid_argument( "vertex is out of bounds" );
        set<int> og;
        for(int i = 0; i < size; i++)
            if(edges[vertex][i])
                og.insert(i);
        return og;
    }

    bool has_outgoing(int vertex) {
        if(vertex < 0 || vertex >= size)
            throw std::invalid_argument( "vertex is out of bounds" );
        for(int i = 0; i < size; i++)
            if(edges[vertex][i])
                return true;
        return false;
    }

    set<int> incoming_edges(int vertex) {
        if(vertex < 0 || vertex >= size)
            throw std::invalid_argument( "vertex is out of bounds" );
        set<int> ic;
        for(int i = 0; i < size; i++)
            if(edges[i][vertex])
                ic.insert(i);
        return ic;
    }

    bool has_incoming(int vertex) {
        if(vertex < 0 || vertex >= size)
            throw std::invalid_argument( "vertex is out of bounds" );
        for(int i = 0; i < size; i++)
            if(edges[i][vertex])
                return true;
        return false;
    }

private:
    int size;
    bool **edges;

    void internal_destructor() {
        for(int i = 0; i < size; i++) {
            delete[] edges[i];
        }
        delete[] edges;
    }

    void internal_copy(const Graph &g) {
        size = g.size;
        edges = new bool*[size];
        for(int i = 0; i < size; i++) {
            edges[i] = new bool[size];
            for(int j = 0; j < size; j++) {
                edges[i][j] = g.edges[i][j];
            }
        }
    }
};

typedef pair<int, int> int_pair;

struct SortMaster {
    bool operator()(const int_pair& lhs, const int_pair& rhs) const {
        return lhs.second < rhs.second;
    }
};

typedef priority_queue<int_pair, vector<int_pair>, SortMaster> pq;

void top_sort_rev(Graph &g, int* depth) {
    bool visited[g.get_size()];
    queue<int> noedge, tmp; // set of vertices with no incoming edges
    int k, l, m; l = 0;
    for(int i = 0; i < g.get_size(); i++) {
        visited[i] = false;
        if(!g.has_outgoing(i))
            noedge.push(i);
    }

    while(!noedge.empty()) {
        m = noedge.size();
        for(int j = 0; j < m; j++) {
            k = noedge.front(); noedge.pop();
            depth[k] = l; // whole purpose of this function to fill depth lol.
            visited[k] = true;

            // remove all edges outgoing from k
            for(int i : g.incoming_edges(k)) {
                if(!visited[i])
                    tmp.push(i); // all incoming edges have out degree one
            }
        }
        while(!tmp.empty()) {
            noedge.push(tmp.front()); tmp.pop();
        }
        l++;
    }
}

void top_sort_school(Graph &g, int k, int* depth) {
    pq noedge, tmp;
    int l, m, acc; acc = 0;

    for(int i = 0; i < g.get_size(); i++) {
        if(!g.has_incoming(i))
            noedge.push(int_pair(i, depth[i]));
    }

    while(!noedge.empty()) {
        acc++;
        m = min(k, (int) noedge.size());
        //cout << "stack sz: " << m << endl;
        for(int i = 0; i < m; i++) {
            l = noedge.top().first; noedge.pop();
            //cout << acc << ": " << l << endl;

            // remove all edges outgoing from k
            for(int j : g.outgoing_edges(l)) {
                g.rem_edge(l, j);
                if(!g.has_incoming(j))
                    tmp.push(int_pair(j, depth[j]));
            }
        }
        while(!tmp.empty()) {
            noedge.push(tmp.top()); tmp.pop();
        }
    }

    cout << acc << endl;
}

/*
This crazy technique uses *2* topological sorts
It times out on test 12

g++ -std=c++11 g-graduation3.cpp -o k

4 2
3 3 4 0

3 3
0 1 2

11 3
9 9 9 9 10 10 10 10 11 11 0

11 3
0 1 1 2 2 2 2 3 3 3 3

8 2
0 1 2 3 0 5 5 5

8 3
2 0 2 0 4 4 2 5 6

9 3
2 0 2 2 0 0 6 6 6
*/
int main() {
    int n, k, a;
    cin >> n >> k;
    int depth[n];
    Graph g = Graph(n);

    for(int i = 0; i < n; i++) {
        depth[i] = 0;
        cin >> a;
        if(a) {
            g.add_edge(i, a - 1);
        }
    }

    top_sort_rev(g, depth);
    for(int i = 0; i < n; i++) printf("%d ", depth[i]);
    cout << endl;
    top_sort_school(g, k, depth);
    return 0;
}


