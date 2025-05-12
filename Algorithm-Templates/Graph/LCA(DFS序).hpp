vector<int> dfn(n + 1), seg(n + 1), siz(n + 1), par(n + 1), dep(n + 1);
int tot = 0;
auto dfs = [&](auto &&dfs, int u, int p) -> void {
    seg[++tot] = u;
    dfn[u] = tot;
    dep[u] = dep[p] + 1;
    par[u] = p;
    siz[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(dfs, v, u);
        siz[u] += siz[v];
    }
};
dfs(dfs, r, 0);

RMQ<int> rmq(seg, [&](int x, int y) {
    if (dep[x] < dep[y]) {
        return x;
    }
    return y;
});

auto lca = [&](int x, int y) -> int {
    if (dfn[x] > dfn[y]) {
        swap(x, y);
    }

    if (dfn[x] + siz[x] - 1 >= dfn[y] + siz[y] - 1) {
        return x;
    }

    return par[rmq.query(dfn[x], dfn[y])];
};
