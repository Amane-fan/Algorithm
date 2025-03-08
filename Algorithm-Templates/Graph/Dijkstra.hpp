{
    using pli = pair<ll, int>;
    dis[s] = 0;
    vector<bool> vis(n + 1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [_, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &[w, v] : adj[u]) {
            if (vis[v] || dis[u] + w >= dis[v]) {
                continue;
            }
            dis[v] = dis[u] + w;
            pq.push({dis[v], v});
        }
    }
}