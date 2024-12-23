const int MAXN = 1e5 + 10, mod = 1e9 + 7;
ll fact[MAXN],infact[MAXN];

ll q_pow(ll a,ll b,int m) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % m;
        }
        b >>= 1;
        a = a * a % m;
    }
    return res;
}

void init() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % mod;
        infact[i] = infact[i - 1] * q_pow(i, mod - 2, mod) % mod;
    }
}

ll comb(int a,int b) {
    return fact[a] * infact[a - b] % mod * infact[b] % mod;
}
