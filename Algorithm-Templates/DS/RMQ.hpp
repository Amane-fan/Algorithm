template<class T>
struct RMQ {
    int n;
    vector<T> a;
    vector<array<T, 30>> f;
    function<T(T, T)> func;

    RMQ() {}

    RMQ(vector<T> init_, function<T(T, T)> func_) {
        init(init_, func_);
    }

    void init(vector<T> &init_, function<T(T, T)> func_) {
        this->a = init_;
        this->func = func_;
        this->n = a.size() - 1;
        this->f.assign(n + 1, {});
        for (int i = 1; i <= n; i++) f[i][0] = a[i];
        for (int j = 1; j <= __lg(n) + 1; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[i][j] = func(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = __lg(r - l + 1);
        return func(f[l][k], f[r - (1 << k) + 1][k]);
    }
};