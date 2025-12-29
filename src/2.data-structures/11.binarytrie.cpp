// BinaryTrie: insert numbers and query max xor with x
struct BinaryTrie {
    struct Node { int next[2]; Node(){ next[0] = next[1] = -1; } };
    vector<Node> t;
    BinaryTrie(){ t.emplace_back(); }
    void clear(){ t.clear(); t.emplace_back(); }
    void insert(int x){
        int v = 0;
        for(int b = 31; b >= 0; --b){
            int bit = (x >> b) & 1;
            if(t[v].next[bit] == -1){
                t[v].next[bit] = (int)t.size();
                t.emplace_back();
            }
            v = t[v].next[bit];
        }
    }
    // maxXor: maximum value of (x xor y) for any y inserted
    int maxXor(int x){
        int v = 0; int ans = 0;
        for(int b = 31; b >= 0; --b){
            int bit = (x >> b) & 1;
            if(t[v].next[1-bit] != -1){
                ans |= (1 << b);
                v = t[v].next[1-bit];
            } else if(t[v].next[bit] != -1){
                v = t[v].next[bit];
            } else return ans;
        }
        return ans;
    }
};