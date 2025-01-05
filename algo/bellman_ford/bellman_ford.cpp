#include <bits/stdc++.h>
using namespace std;

/// bellman ford algorithm
/// given directed graph withwith real value edge weights and a source node
/// return cost an path from source node to every other node
/// or find the nodes in a negative cycle
/// output unreachable for nodes disconnected from source

/// in:
/// [number of nodes] [number of edges]
/// [source node]
/// (for each edge) [from node] [to node] [integer cost]

/**
in:
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

in:
5 6
1
1 2 1
2 3 10
3 1 10
2 4 1
4 5 0
5 3 0

out:
1, cost: 0, path: 1
2, cost: 1, path: 1 2
3, cost: 2, path: 1 2 4 5 3
4, cost: 2, path: 1 2 4
5, cost: 2, path: 1 2 4 5

in:
5 5
1
1 2 10
2 3 10
2 4 -1
4 5 -1
5 2 -1

out:
cycle detected
2 4 5

g++ -std=c++20 bellman_ford.cpp -o k
./k < tests/bellman-ford-1.in
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
        adj[i_from].push_back(std::make_pair(i_to, cost));
    }

    // compute distances and predecessors
    int new_cost;
    for (int k = 0; k < n_nodes - 1; k++) {
        // iterate through each edge
        for (int i_from = 0; i_from < n_nodes; i_from++) {
            for (auto [i_to, cost] : adj[i_from]) {
                
                if (distances[i_from] < std::numeric_limits<int>::max()) {
                    new_cost = distances[i_from] + cost;
                } else {
                    new_cost = std::numeric_limits<int>::max();
                }
                
                if(new_cost < distances[i_to]) {
                    // reassign distance and predessor because we found a shorter route
                    distances[i_to] = new_cost;
                    predecessors[i_to] = i_from;
                }
            }
        }
    }

    // detect negative cycles
    bool has_cycle = false;
    int i_cycle_candidate;
    for (int i_from = 0; i_from < n_nodes; i_from++) {
        for (auto [i_to, cost] : adj[i_from]) {

            if (distances[i_from] < std::numeric_limits<int>::max()) {
                new_cost = distances[i_from] + cost;
            } else {
                new_cost = std::numeric_limits<int>::max();
            }

            if(new_cost < distances[i_to]) {
                // cycle is detected, get candidates for cycle
                has_cycle = true;
                i_cycle_candidate = i_to;
            }
        }
    }
    
    if (has_cycle) {
        // find a node in cycle
        std::vector<bool> visited(n_nodes, false);
        visited[i_cycle_candidate] = true;
        int j = predecessors[i_cycle_candidate];
        while (!visited[j]) {
            visited[j] = true;
            j = predecessors[j];
        }

        // find nodes in cycle
        int i_in_cycle = j;
        std::vector<int> cycle = {i_in_cycle};
        cycle.reserve(n_nodes);
        j = predecessors[i_in_cycle];
        while (j != i_in_cycle) {
            cycle.push_back(j);
            j = predecessors[j];
        }
        
        // print cycle
        std::cout << "cycle detected\n";
        for (int i : cycle | std::views::reverse) {
            std::cout << i+1 << " ";
        }
        std::cout << std::endl;
    } else {
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
                };
                
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
    }

    return 0;
}

