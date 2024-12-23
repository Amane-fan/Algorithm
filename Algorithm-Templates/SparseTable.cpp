struct SparseTable {
    vector<vector<int>> f;
    SparseTable(vector<int> &a, int n) {
        int logN = __lg(n) + 1;
        Log.resize(n + 1);
        f.assign(n + 1, vector<int>(logN + 1));
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
        int s = __lg(r - l + 1);
        return max(f[l][s], f[r - (1 << s) + 1][s]);
    }
};