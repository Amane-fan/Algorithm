constexpr int N = 1e8;
bitset<N + 1> is;
vector<int> prime;

void ErSieve() {
    for (int i = 2; i <= N; i++) {
        if (is[i]) continue;
        prime.push_back(i);
        for (ll j = 1LL * i * i; j <= N; j += i) {
            is.set(j);
        }
    }
}
