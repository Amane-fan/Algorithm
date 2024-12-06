struct SparseTable {
    int logN;
    vector<vector<int>> f;
    vector<int> Log;
    SparseTable(int n, vector<int> &a) {
        init(n,a);
    }
    void init(int n, vector<int> &a) {
        logN = __lg(n) + 1;
        Log.resize(n + 1);
        f.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            f[i].resize(logN + 1);
        }
        Log[1] = 0;
        for (int i = 2; i <= n; i++) {
            Log[i] = Log[i / 2] + 1;
        }
        for (int i = 1; i <= n; i++) {
            f[i][0] = a[i];
        }
        for (int j = 1; j <= logN; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int getMax(int l, int r) {
        int s = Log[r - l + 1];
        return max(f[l][s], f[r - (1 << s) + 1][s]);
    }
};
