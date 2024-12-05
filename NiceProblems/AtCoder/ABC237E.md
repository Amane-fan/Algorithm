> 题目链接：https://atcoder.jp/contests/abc237/tasks/abc237_e

> 标签：贪心，图论，最短路

## 思路：

题目的意思是说，从低往高会减少两倍高度差值，从高往低会增加一倍差值

考虑减少也是一倍的时候，假设我们已经找到了一条路径    $v_1 - v_2 - v_3 ... v_m$

假设从 $v_1 - v_2$ 时，$h_2 > h_1$， 那么有这条路产生的贡献就是 $-(h_2 - h_1) = +(h_1 - h_2)$

如果是 $h_1 > h_2$ ，那么有这条路产生的贡献就是 $h_1 - h_2$

所以，**整条路所产生的贡献就是** $h_1 - h_2 + h_2 - h_3 +...+h_m = h_1 - h_m$

那么如果减少的是两倍，如何做呢？

我们可以理解为，从低往高会另外产生 $h_1 - h_2$ 的代价，从高往低不会有变化，因为是增加一倍

建图，从低往高的边权设为他们之间的差值，否则设为0

如果我们已经确定了一条路，那么这条路的贡献结果是 $h_1 - h_m - dis_m ,dis_i$代表从1到i的边权总和，也就是代价

要使结果最大，就需要让$dis_m$最小，因此，求出从 1 出发的单源最短路径即可

## Code:

```cpp
constexpr ll inf = 1e18;
using PLI = pair<ll,int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    vector<vector<array<int,2>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        if (h[u] > h[v]) {
            adj[u].push_back({v,0});
            adj[v].push_back({u,h[u] - h[v]});
        }
        else {
            adj[u].push_back({v,h[v] - h[u]});
            adj[v].push_back({u,0});
        }
    }

    vector<ll> dis(n + 1,inf);
    vector<bool> vis(n + 1);
    priority_queue<PLI, vector<PLI>, greater<>> pq;
    pq.push({0, 1});
    dis[1] = 0;
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        int u = p.se;
        if (vis[u]) continue;
        vis[u] = true;
        for (auto & e : adj[u]) {
            int v = e[0], w = e[1];
            if (vis[v] || w + dis[u] >= dis[v]) continue;
            dis[v] = dis[u] + w;
            pq.push({dis[v], v});
        }
    }

    ll ans = -inf;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, -dis[i] + h[1] - h[i]);
    }
    cout << ans << '\n';
    return 0;
}
```

