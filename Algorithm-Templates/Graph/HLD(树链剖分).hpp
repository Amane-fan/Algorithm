struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> siz, par, hvy, dep, dfn, seq, top, out;
    int cur;
    HLD() {}
    HLD(int n) {
        cur = 0;
        this->n = n;
        adj.resize(n + 1);
        siz.resize(n + 1);
        par.resize(n + 1);
        hvy.resize(n + 1);
        dep.resize(n + 1);
        dfn.resize(n + 1);
        seq.resize(n + 1);
        top.resize(n + 1);
        out.resize(n + 1);
    }
    void work(int root = 1) {
        dfs1(root, 0);
        dfs2(root, 0, root);
        for (int i = 1; i <= n; i++) {
            out[i] = dfn[i] + siz[i] - 1;
        }
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs1(int u, int p) {
        par[u] = p;
        siz[u] = 1;
        dep[u] = dep[p] + 1;
        int mx = 0, hc = 0;
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > mx) {
                mx = siz[v];
                hc = v;
            }
        }
        hvy[u] = hc;
    }
    void dfs2(int u, int p, int t) {
        seq[++cur] = u;
        dfn[u] = cur;
        top[u] = t;
        if (hvy[u] != 0) {
            dfs2(hvy[u], u, t);
        }
        for (auto v : adj[u]) {
            if (v == p || v == hvy[u]) {
                continue;
            }
            dfs2(v, u, v);
        }
    }
    bool isAncester(int x, int y) {
        return (dfn[x] <= dfn[y]) && (out[x] >= out[y]);
    }
    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) {
                swap(x, y);
            }
            x = par[top[x]];
        }
        return dep[x] <= dep[y] ? x : y;
    }
    int dis(int x, int y) {
        return dep[x] + dep[y] - dep[lca(x, y)] * 2;
    }
    vector<pair<int, int>> getPath(int x, int y) {
        vector<pair<int, int>> res;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) {
                swap(x, y);
            }
            res.emplace_back(dfn[top[x]], dfn[x]);
            x = par[top[x]];
        }
        res.emplace_back(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]));
        return res;
    }
};