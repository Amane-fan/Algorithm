bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int findPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const int P = findPrime(rng() % 900'000'000 + 900'000'000),
base = std::uniform_int_distribution<int>(8e8, 9e8)(rng);

struct Hash {
    vector<ll> h;
    vector<ll> p;
    Hash(string &s) {
        init(s);
    }
    void init(string &s) {
        int n = s.size();
        s = " " + s;
        p.resize(n + 1);
        h.resize(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++) {
            p[i] = p[i - 1] * base % P;
            h[i] = (h[i - 1] * base + s[i]) % P;
        }
    }
    ll get(int l, int r) {
        return (h[r] - h[l - 1] * p[r - l + 1] % P + P) % P;
    } 
};