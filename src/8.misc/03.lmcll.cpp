ll lcmll(ll a,ll b){ 
    if(a==0||b==0)return 0;
    return a/gcdll(a,b)*b;
}