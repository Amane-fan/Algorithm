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
base = uniform_int_distribution<>(8e8, 9e8)(rng);
