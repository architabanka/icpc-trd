const int NCR_MAX = 200000; // adjust if you need larger
static ll factN[NCR_MAX+1], invfactN[NCR_MAX+1];
void init_nCr(int N = NCR_MAX){
    factN[0] = 1;
    for(int i=1;i<=N;i++) factN[i] = factN[i-1] * i % MOD;
    invfactN[N] = modinv(factN[N]);
    for(int i=N;i>0;i--) invfactN[i-1] = invfactN[i] * i % MOD;
}
ll nCr(int n, int r){
    if(r < 0 || r > n) return 0;
    return factN[n] * invfactN[r] % MOD * invfactN[n-r] % MOD;
}
