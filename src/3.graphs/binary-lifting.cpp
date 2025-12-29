// Preprocessing: O(N log N)
// Query: O(log N), Tree static (no updates)
struct LCA {
    int n;                      // number of nodes
    int LOG;                    // max power of 2 needed
    vector<vector<int>> up;     // up[v][j] = 2^j-th ancestor of v
    vector<vector<ll>> sum; // sum[v][j] = sum of values from v up to up[v][j]
    vector<vector<ll>> mx;  // mx[v][j]  = maximum value on path v -> up[v][j]
    vector<int> depth;          // depth of each node from root
    vector<ll> val;      // value stored at each node

    LCA() {}
    // Constructor: builds LCA from adjacency list and node values
    LCA(const vector<vector<int>>& adj,
        const vector<ll>& values,
        int root = 0)
    {
        init(adj, values, root);
    }
    // Initialize and preprocess binary lifting tables
    void init(const vector<vector<int>>& adj,
              const vector<ll>& values,
              int root = 0)
    {
        n = adj.size();
        val = values;
        // LOG ≈ log2(n)
        LOG = max(1, (int)ceil(log2(max(1, n))) + 1);

        up.assign(n, vector<int>(LOG));
        sum.assign(n, vector<ll>(LOG, 0));
        mx.assign(n, vector<ll>(LOG, LLONG_MIN));
        depth.assign(n, 0);

        // DFS from root to fill tables
        dfs_build(adj, root, root);
    }
    // DFS to build depth[], up[][], sum[][], mx[][]
    void dfs_build(const vector<vector<int>>& adj, int v, int p) {
        // Base ancestor (2^0)
        up[v][0] = p;
        sum[v][0] = val[v];   // sum of path of length 1 (node itself)
        mx[v][0] = val[v];    // max of path of length 1

        // Precompute ancestors at powers of two
        for (int j = 1; j < LOG; j++) {
            up[v][j] = up[ up[v][j-1] ][j-1];
            sum[v][j] = sum[v][j-1] + sum[ up[v][j-1] ][j-1];
            mx[v][j] = max(mx[v][j-1], mx[ up[v][j-1] ][j-1]);
        }

        // DFS traversal
        for (int to : adj[v]) {
            if (to == p) continue;
            depth[to] = depth[v] + 1;
            dfs_build(adj, to, v);
        }
    }

    // Lift node u by k levels upward
    // Also accumulates sum and max along the lifted path
    pair<ll, ll> lift(int& u, int k) {
        ll path_sum = 0;
        ll path_max = LLONG_MIN;

        for (int j = 0; j < LOG; j++) {
            if (k & (1 << j)) {
                path_sum += sum[u][j];
                path_max = max(path_max, mx[u][j]);
                u = up[u][j];
            }
        }
        return {path_sum, path_max};
    }

    // LCA query (standard binary lifting)
    int query(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);

        // Lift a to same depth as b
        int diff = depth[a] - depth[b];
        for (int j = 0; j < LOG; j++)
            if (diff & (1 << j))
                a = up[a][j];

        if (a == b) return a;

        // Lift both until their ancestors differ
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        // Parent of both is LCA
        return up[a][0];
    }

    // ----------------------------------------------------------
    // Path query: returns {sum, max} on path a -> b
    // ----------------------------------------------------------
    pair<ll, ll> path_query(int a, int b) {
        ll total_sum = 0;
        ll total_max = LLONG_MIN;

        // Ensure a is deeper
        if (depth[a] < depth[b]) swap(a, b);
        // Lift a to depth of b
        auto res = lift(a, depth[a] - depth[b]);
        total_sum += res.first;
        total_max = max(total_max, res.second);

        // If b was ancestor of a
        if (a == b) {
            total_sum += val[a];
            total_max = max(total_max, val[a]);
            return {total_sum, total_max};
        }
        // Lift both nodes until just below LCA
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                total_sum += sum[a][j] + sum[b][j];
                total_max = max({total_max, mx[a][j], mx[b][j]});
                a = up[a][j];
                b = up[b][j];
            }
        }
        // Add a, b, and LCA itself
        total_sum += val[a] + val[b] + val[up[a][0]];
        total_max = max({total_max, val[a], val[b], val[up[a][0]]});

        return {total_sum, total_max};
    }
    // Distance between two nodes using LCA
    int distance(int a, int b) {
        int c = query(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};
