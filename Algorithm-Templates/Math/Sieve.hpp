constexpr int N = 1e8;
vector<int> prime;
vector<int> minp(N + 1);

void Sieve() {
    for (int i = 2; i <= N; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            prime.push_back(i);
        }

        for (auto &p : prime) {
            if (p * i > N) {
                break;
            }
            minp[p * i] = p;
            if (minp[i] == p) {
                break;
            }
        }
    }
}