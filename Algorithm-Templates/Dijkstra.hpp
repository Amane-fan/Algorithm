auto dijkstra = [&](int s) -> vector<ll> {
    vector<ll> dis(n + 1, inf);
    vector<bool> vis(n + 1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dis[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        int u = p.se;
        if (vis[u]) continue;
        vis[u] = true;
        for (auto e : adj[u]) {
            int v = e[0], w = e[1];
            if (vis[v] || dis[u] + w >= dis[v]) continue;
            dis[v] = dis[u] + w;
            pq.push({dis[v], v});
        }
    }
    return dis;
};