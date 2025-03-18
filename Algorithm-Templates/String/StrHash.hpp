using ull = unsigned long long;
constexpr ull mod = (1ull << 61) - 1;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ull> dist(mod / 2, mod - 1);
const ull base = dist(rnd);

struct Hash {
    vector<ull> h;
    vector<ull> p;
    Hash() {}
    Hash(const string &s) {
        init(s);
    }
    ull add(ull a, ull b) {
        a += b;
        if (a >= mod) a -= mod;
        return a;
    }
    ull mul(ull a, ull b) {
        __uint128_t c = __uint128_t(a) * b;
        return add(c >> 61, c & mod);
    }
    void init(const string &s) {
        int n = s.size() - 1;
        p.resize(n + 1);
        h.resize(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++) {
            p[i] = mul(p[i - 1], base);
            h[i] = mul(h[i - 1], base);
            h[i] = add(h[i], s[i]);
        }
    }
    ull get(int l, int r) {
        return add(h[r], mod - mul(h[l - 1], p[r - l + 1]));
    } 
};