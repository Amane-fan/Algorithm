template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int N): n(N - 1),a(N) {}
    void add(int x,T v) {
        for (int i = x; i <= n; i += (i & -i)) {
            a[i] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            ans += a[i];
        }
        return ans;
    }
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
