// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends

const int N = 200000;
int low[N], vis[N], scomp[N], scompNum, I;
vector<int> adj[N];
stack<int> verts;
void scc(int u) {
    low[u] = vis[u] = ++I;
    verts.push(u);
    for (int v : adj[u]) {
        if (!vis[v])
            scc(v);
        if (scomp[v] == -1)
            low[u] = min(low[u], low[v]);
    }
    if (vis[u] <= low[u]) {
        int v;
        do {
            v = verts.top();
            verts.pop();
            scomp[v] = scompNum;
        } while (v != u);
        ++scompNum;
    }
}

void get_scc(int n) {
    memset(vis,0,sizeof vis);
    memset(scomp,-1,sizeof scomp);
    scompNum=I=0;
    for (int i=0; i<n; ++i)
        if (!vis[i]) scc(i);
}

class Solution
{
	public:
	int sol1(int V, vector<int> _adj[]) {
	    for(int i = 0; i < V; i++)
            adj[i] = _adj[i];
        get_scc(V);
        return scompNum;
	}
	
	int sol2(int V, vector<int> adj[]) {
	    int i, j, k;
        int u, v, curr;
	    int n = V;
        //Find SCC using iterative DFS
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
                    // if node is unvisited
                    // we cannot check that node has been visited before recursive call
                    // we can ONLY check that node has been visited within the call
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
                    // only want to backtrack on u when all edges from u has been recursed
                    // this can be done by adding same node to stack multiple times to keep track of how many recursive calls have been made
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

        return compi;
	}
	//Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<int> _adj[]) {
        // solution 1
        // return sol1(V, _adj);
        
        // solution 2
        return sol2(V, _adj);
    }
};

// { Driver Code Starts.


int main()
{
    
    int t;
    cin >> t;
    while(t--)
    {
    	int V, E;
    	cin >> V >> E;

    	vector<int> adj[V];

    	for(int i = 0; i < E; i++)
    	{
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    	}

    	Solution obj;
    	cout << obj.kosaraju(V, adj) << "\n";
    }

    return 0;
}

  // } Driver Code Ends
