struct Comb {
    int n;
    vector<ll> fac;
    vector<ll> invfac;
    Comb(){}
    Comb(int n_) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        fac.assign(n + 1, 1);
        invfac.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
            invfac[i] = invfac[i - 1] * q_pow(i, mod - 2, mod) % mod;
        }
    }
    ll comb(int a, int b) {
        return fac[a] * invfac[a - b] % mod * invfac[b] % mod;
    }
};