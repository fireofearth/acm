// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
//User function template for C++

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
    }
    for (int v : adj[u]) {
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

bool sorter(vector<int> const& lhs, vector<int> const& rhs) {
    if(lhs.size() == 0) return true;
    if(rhs.size() == 0) return false;
    return lhs[0] < rhs[0];
}

class Solution
{
	public:
    //Function to return a list of lists of integers denoting the members 
    //of strongly connected components in the given graph.
    vector<vector<int>> sol1(int V, vector<int> _adj[]) {
        for(int i = 0; i < V; i++)
            adj[i] = _adj[i];
        get_scc(V);
        vector<vector<int>> sol(scompNum);
        int c;
        for(int i = 0; i < V; i++) {
            c = scomp[i];
            sol[c].push_back(i);
        }
        sort(sol.begin(), sol.end(), &sorter);
        return sol;
    }
    
    vector<vector<int>> sol2(int V, vector<int> adj[]) {
        
        int n = V; // nodes
        int i, j, k;
        int u, v, curr, c;
    
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
                    lowests[u] = indices[u] = index; index++;
                    z.push(u);
    
                    // recurse DFS
                    for(int v : adj[u]) {
                        s.push(v);
                        t.push(u);
                    }
                    if(t.empty() || u != t.top()) t.push(u);
                    //printf("at u=%d low:%d  ind:%d\n", u, lowests[u], indices[u]);
    
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
                            //printf("at u=%d; v=%d %d\n", u, v, compi);
                            v = z.top(); z.pop();
                            comp[v] = compi;
                        } while(u != v);
                        compi++;
                    }
                }
            }
        }


        vector<vector<int>> sol(compi);
        for(int i = 0; i < V; i++) {
            c = comp[i];
            sol[c].push_back(i);
        }
        sort(sol.begin(), sol.end(), &sorter);
        return sol;
    }
    
    vector<vector<int>> tarjans(int V, vector<int> _adj[]) {
        // solution 1
        return sol1(V, _adj);
        
        // solution 2
        // return sol2(V, _adj);
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
        vector<vector<int>> ptr = obj.tarjans(V, adj);

        for(int i=0; i<ptr.size(); i++)
        {
            for(int j=0; j<ptr[i].size(); j++)
            {
                if(j==ptr[i].size()-1)
                    cout<<ptr[i][j];
                else
                    cout<<ptr[i][j]<<" ";
            }
            cout<<',';
        }
        cout<<endl;
    }

    return 0;
}

  // } Driver Code Ends
