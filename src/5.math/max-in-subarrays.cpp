// sliding_window_max: returns max for every subarray of size k
vector<ll>sliding_window_max(const vector<ll>& a, int k){
    int n=(int)a.size();
    vector<ll> res;
    if(k <= 0 || k > n) return res;
    deque<int>dq; // store indices, decreasing values
    for(int i=0;i<n;i++){
        while(!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while(!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if(i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}