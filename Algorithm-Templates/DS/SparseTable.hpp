template <class T, class F>
struct SparseTable {
    int n;
    F fun;
    vector<vector<T>> f;
    SparseTable(const vector<T> &a, const F &fun_): n(int(a.size()) - 1), fun(fun_) {
        int logN = __lg(n) + 1;
        f.assign(n + 1, vector<T>(logN + 1));
        for (int i = 1; i <= n; i++) {
            f[i][0] = a[i];
        }
        for (int j = 1; j <= logN; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[i][j] = fun(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T query(int l, int r) {
        assert(1 <= l && l <= r && r <= n);
        int s = __lg(r - l + 1);
        return fun(f[l][s], f[r - (1 << s) + 1][s]);
    }
};