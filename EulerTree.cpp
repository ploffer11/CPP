class Tree
{
private:
    vector<vector<pair<int, ll>>> adj; 
    vector<int> lg2, euler, dis;
    int v, e, root;
    
    void dfs()
    
public:
    Tree(int n, int root = 1) : v(n), e(0), root(root), euler(2 * n), dis(n + 1), lg2(n + 1)
    {
        
    }
    
    void add_edge(int u, int v, ll cap = 1)
    {
        adj[u].push_back({v, cap});
        adj[v].push_back({u, cap});
        if (++e == v - 1)
            dfs(root, 0);
    }
    
}