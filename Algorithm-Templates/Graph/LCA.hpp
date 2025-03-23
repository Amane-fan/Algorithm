int N = __lg(n - 1);
vector<int> dep(n + 1);
// f[u][i] 表示u节点往上跳 2^i 层所到达的节点，若无法到达，则为0
vector f(n + 1, vector<int>(N + 1));

auto dfs = [&](auto &&dfs, int u, int p) -> void {
    dep[u] = dep[p] + 1;
    f[u][0] = p;
    for (int i = 1; i <= N; i++) {
        // 先往上跳 2^(i - 1) 所到达的节点再网上跳 2^(i - 1)
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(dfs, v, u);
    }
};
dfs(dfs, s, 0);

auto lca = [&](int x, int y) -> int {
    // 保证x深度最大
    if (dep[x] < dep[y]) swap(x, y);
    // 先让x往上跳d层到达同一深度
    int d = dep[x] - dep[y];
    // 拆位按整次幂跳
    for (int i = __lg(d); i >= 0; i--) {
        if (d >> i & 1) {
            x = f[x][i];
        }
    }

    if (x == y) return x;
    // 到达同一深度后，从大到小按照2^i试探着跳，如果跳过了，则节点相同，否则一起向上跳
    // 最后一定会达到lca的下一层
    for (int i = N; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
};
