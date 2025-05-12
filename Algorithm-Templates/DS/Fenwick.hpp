template <class T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int N): n(N), a(N + 1) {}
    void add(int x, const T &v) {
        for (int i = x; i <= n; i += (i & -i)) {
            a[i] += v;
        }
    }
    void modify(int x, const T &v) {
        add(x, v - rangeQuery(x, x));
    }
    T query(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            ans += a[i];
        }
        return ans;
    }
    T rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};
