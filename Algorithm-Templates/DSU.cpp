struct DSU {
    std::vector<int> p,cnt;
    DSU(){}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        p.resize(n);
        std::iota(p.begin(),p.end(),0);
        cnt.assign(n,1);
    }
    int find(int x) {
        if (x != p[x]) {
            p[x] = find(p[x]);
        }
        return p[x];
    }
    bool merge(int x,int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        cnt[x] += cnt[y];
        p[y] = x;
        return true;
    }
    int size(int x) {
        return cnt[find(x)];
    }
    bool same(int x,int y) {
        return find(x) == find(y);
    }
};