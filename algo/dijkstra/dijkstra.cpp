#include <bits/stdc++.h>
using namespace std;

/// dijkstra algorithm
/// given directed graph with positive real value edge weights and a source node
/// return cost an path from source node to every other node
/// output unreachable for nodes disconnected from source
/// does not work with negative edge weights; use Bellman Ford algorithm instead.
/// time complexity O(E + V * log V)

/// in:
/// [number of nodes] [number of edges]
/// [source node]
/// (for each edge) [from node] [to node] [integer cost]

struct Compare {
    bool operator()(std::pair<int,int> a, std::pair<int,int> b) {
        return a.second > b.second;
    }
};

/**
5 3
1
1 2 10
1 3 20
4 5 30

out:
1, cost: 0, path: 1
2, cost: 10, path: 1 2
3, cost: 20, path: 1 3
4 unreachable
5 unreachable

g++ -std=c++20 dijkstra.cpp -o k
./k < tests/dijkstra-1.in
*/
int main () {
    // initialize parameters
    int n_nodes, n_edges, i_source;
    std::cin >> n_nodes >> n_edges >> i_source;
    i_source--;

    // initialize distances to infinity except source node
    std::vector<int> distances(n_nodes, std::numeric_limits<int>::max());
    distances[i_source] = 0;

    // initialize predecessor
    std::vector<int> predecessors(n_nodes, -1);

    // initialize adjacency matrix with costs to edges
    // adj[from] = {to, cost}
    std::vector<std::vector<std::pair<int,int>>> adj(n_nodes);
    int i_from, i_to, cost;
    for (int j = 0; j < n_edges; j++) {
        std::cin >> i_from >> i_to >> cost;
        i_from--; i_to--;
        adj[i_from].push_back({i_to, cost});
    }

    // initialize adjacency list with costs to edges
    std::vector<int> visited(n_nodes, false);

    // compute distances and predecessors
    // use priority queue effectively rank paths to visit by distnace
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, Compare> pq;
    pq.push({i_source, 0});
    while (!pq.empty()) {
        auto [i, distance] = pq.top();
        pq.pop();
        if (visited[i]) {
            continue;
        }

        visited[i] = true;
        for (auto [j, cost] : adj[i]) {
            int new_distance = distances[i];
            if (new_distance < std::numeric_limits<int>::max()) {
                new_distance += cost;
            }

            if (new_distance < distances[j]) {
                // if we found a shorter distance from i_source to j through i
                // record the path
                distances[j] = new_distance;
                predecessors[j] = i;
                // if j is already in the priority queue with a longer distance
                // then this one is prioritized over the existing entry
                // use the visited map to select this entry, and skip over the other entires
                pq.push({j, new_distance});
            }
        }
    }

    // print cost and path to each node from source
    std::vector<int> path;
    path.reserve(n_nodes);
    for (int i = 0; i < n_nodes; i++) {
        if (distances[i] < std::numeric_limits<int>::max()) {
            // path from i_source to i exists with finite distance
            std::cout << i+1 << ", cost: " << distances[i];

            // get the path from i_source to i
            path = {i};
            int j = i;
            while (j != i_source) {
                j = predecessors[j];
                path.push_back(j);
            }
            
            // print out the path from i_source to i
            std::cout << ", path: ";
            for (int j : path | std::views::reverse) {
                std::cout << j+1 << " ";
            }
            std::cout << std::endl;
        } else {
            // no path from i_source to i
            std::cout << i+1 << " unreachable\n";
        }
    }

    return 0;
}

