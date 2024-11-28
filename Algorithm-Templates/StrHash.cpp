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

const int N = 1e5 + 10;
ll p[N],h[N];

void init(std::string s) {
    int n = s.size();
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = (h[i - 1] * base + s[i]) % P;
        p[i] = p[i - 1] * base % P;
    }
}

ll get(int l,int r) {
    return (h[r] - (h[l - 1] * p[r - l + 1]) % P + P) % P;
}