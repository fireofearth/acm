#include <bits/stdc++.h>
using namespace std;

/// depth first search
/// given directed graph with no weights
/// and a source and destination node
/// find a path from souce and destination
/// or output unreachable

/// in:
/// [number of nodes] [number of edges]
/// [source node] [destination node]
/// (for each edge) [from node] [to node]

/**
in:
3 2
1 2
1 2
1 3

out:
1 2

in:
7 7
2 5
2 1
1 3
3 4
4 5
2 6
6 4
6 7

out:
2 6 4 5

g++ -std=c++20 dfs.cpp -o k
*/
int main () {
    // initialize parameters
    int n_nodes, n_edges, i_src, i_dst;
    std::cin >> n_nodes >> n_edges >> i_src >> i_dst;
    i_src--;
    i_dst--;
    
    // initialize adjacency matrix
    // adj[from] = {to}
    std::vector<std::vector<int>> adj(n_nodes);
    int i_from, i_to;
    for (int j = 0; j < n_edges; j++) {
        std::cin >> i_from >> i_to;
        i_from--; i_to--;
        adj[i_from].push_back(i_to);
    }

    // perform dfs to get path
    bool has_found = false;
    std::vector<int> path;
    path.reserve(n_nodes);
    std::vector<int> visited(n_nodes, false);
    // dfs.top() = {node,depth}
    std::stack<std::pair<int, int>> dfs;
    dfs.push(std::make_pair(i_src, 0));
    while(!dfs.empty()) {
        auto [i, depth] = dfs.top();
        dfs.pop();

        while (path.size() > depth) {
            path.pop_back();
        }

        path.push_back(i);
        visited[i] = true;
        if (i == i_dst) {
            has_found = true;
            break;
        }

        for (int j : adj[i]) {
            if (visited[j]) {
                continue;
            }

            dfs.push(std::make_pair(j, depth + 1));
        }
    }

    if (has_found) {
        std::cout << "path: ";
        for (int i : path) {
            std::cout << i+1 << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "unreachable\n";
    }

    return 0;
}

