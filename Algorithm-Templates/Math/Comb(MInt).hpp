struct Comb {
    int n;
    vector<Z> _fac, _infac, _inv;
    Comb(): n{0}, _fac{1}, _infac{1}, _inv{0} {}
    Comb(int m): Comb() {
        init(m);
    }
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _infac.resize(m + 1);
        _inv.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _infac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _infac[i - 1] = _infac[i] * i;
            _inv[i] = _infac[i] * _fac[i - 1];
        }
        n = m;
    }
    Z fac(int m) {
        if (m > n) init(m * 2);
        return _fac[m];
    }
    Z infac(int m) {
        if (m > n) init(m * 2);
        return _infac[m];
    }
    Z inv(int m) {
        if (m > n) init(m * 2);
        return _inv[m];
    }
    Z C(int a, int b) {
        if (a < b || b < 0) return 0;
        return fac(a) * infac(a - b) * infac(b);
    }
    Z A(int a, int b) {
        if (a < b || b < 0) return 0;
        return fac(a) * infac(a - b);
    }
    Z A(int a) {
        return fac(a);
    }
} comb;