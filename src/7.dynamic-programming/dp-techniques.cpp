// 1D DP: Fibonacci (iterative)
ll fib(int n){
    if(n < 2) return n;
    ll a = 0, b = 1;
    for(int i=2;i<=n;i++){
        ll c = a + b;
        a = b; b = c;
    }
    return b;
} 
// 0/1 Knapsack (1D optimized)
int knapsack01(const vector<int>& wt, const vector<int>& val, int W){
    int n = wt.size();
    vector<int> dp(W+1, 0);
    for(int i=0;i<n;i++){
        for(int w=W; w>=wt[i]; w--){
            dp[w] = max(dp[w], dp[w-wt[i]] + val[i]);
        }
    }
    return dp[W];
}
// Subset sum (boolean)
bool subset_sum(const vector<int>& a, int S){
    vector<char> dp(S+1, 0);
    dp[0] = 1;
    for(int x: a){
        for(int s=S; s>=x; --s) if(dp[s-x]) dp[s] = 1;
    }
    return dp[S];
}
// LCS (2D DP)
int LCS(const string &A, const string &B){
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][m];
}
// LIS length O(n log n)
int LIS_length(const vector<int>& a){
    vector<int> tail;
    for(int x: a){
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if(it == tail.end()) tail.push_back(x);
        else *it = x;
    }
    return (int)tail.size();
}
// Kadane's algorithm (max subarray sum)
ll kadane(const vector<ll>& a){
    ll best = LLONG_MIN, cur = 0;
    for(ll x: a){
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}
// Grid DP: count paths avoiding obstacles (0 = free, 1 = blocked)
ll grid_paths(const vector<vector<int>>& grid){
    int n = grid.size(); if(n==0) return 0;
    int m = grid[0].size();
    vector<vector<ll>> dp(n, vector<ll>(m, 0));
    if(grid[0][0] == 0) dp[0][0] = 1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]) continue;
            if(i) dp[i][j] += dp[i-1][j];
            if(j) dp[i][j] += dp[i][j-1];
        }
    }
    return dp[n-1][m-1];
}
// Tree DP example: compute subtree sizes (requires global adj)
void compute_subsize_dfs(int v, int p, const vector<vector<int>>& adj, vector<int>& subsize){
    subsize[v] = 1;
    for(int u: adj[v]) if(u != p){
        compute_subsize_dfs(u, v, adj, subsize);
        subsize[v] += subsize[u];
    }
}
// Bitmask DP (TSP style) -careful with n <= ~20
int tsp_bitmask_dp(const vector<vector<int>>& cost){
    int n = cost.size();
    int N = 1 << n;
    const int INFINT = 1e9;
    vector<vector<int>> dp(N, vector<int>(n, INFINT));
    dp[1][0] = 0; // start at 0
    for(int mask=1; mask<N; ++mask){
        for(int u=0; u<n; ++u) if(mask & (1<<u)){
            for(int v=0; v<n; ++v) if(!(mask & (1<<v))){
                dp[mask | (1<<v)][v] = min(dp[mask | (1<<v)][v], dp[mask][u] + cost[u][v]);
            }
        }
    }
    int ans = INFINT;
    for(int u=0; u<n; ++u) ans = min(ans, dp[N-1][u] + cost[u][0]);
    return ans;
}
// Deque DP optimization example:
// dp[i] = a[i] + min(dp[j]) for j in [i-k, i-1]
ll deque_dp_min_example(const vector<ll>& a, int k){
    int n = a.size();
    vector<ll> dp(n, LINF);
    deque<int> dq;
    dp[0] = a[0];
    dq.push_back(0);
    for(int i=1;i<n;i++){
        while(!dq.empty() && dq.front() < i - k) dq.pop_front();
        dp[i] = a[i] + dp[dq.front()];
        while(!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back();
        dq.push_back(i);
    }
    return dp[n-1];
}
