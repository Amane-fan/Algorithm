bool gauss(vector<vector<int>> &a) {
    int n = (int)a.size() - 1;
    for (int i = 1; i <= n; i++) {
        int r = i;
        for (int k = i; k <= n; k++) {
            if (fabs(a[k][i]) > eps) {
                r = k;
                break;
            }
        }
        if (r != i) swap(a[i], a[r]);
        if (fabs(a[i][i]) < eps) return false;

        for (int j = n + 1; j >= i; j--) {
            a[i][j] /= a[i][i];
        }
        for (int k = i + 1; k <= n; k++) {
            for (int j = n + 1; j >= i; j--) {
                a[k][j] -= a[i][j] * a[k][i];
            }
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            a[i][n + 1] -= a[i][j] * a[j][n + 1];
        }
    }
    return true;
}