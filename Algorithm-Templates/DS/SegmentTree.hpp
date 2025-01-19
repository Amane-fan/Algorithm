template <class Info>
struct SegmentTree {
    #define ls(x) (x << 1)
    #define rs(x) (x << 1 | 1)
    int n;
    vector<Info> info;
    SegmentTree(): n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(vector<Info>(n_ + 1, v_));
    }
    SegmentTree(vector<Info> init_) {
        init(init_);
    }
    void init(vector<Info> init_) {
        n = init_.size() - 1;
        info.assign(n << 2, Info());
        function<void(int, int, int)> build = [&](int id, int l, int r) {
            if (l == r) {
                info[id] = init_[l];
                return;
            }
            int mid = l + r >> 1;
            build(ls(id), l, mid);
            build(rs(id), mid + 1, r);
            pushUp(id);
        };
        build(1, 1, n);
    }
    void pushUp(int id) {
        info[id] = info[ls(id)] + info[rs(id)];
    }
    void modify(int id, int l, int r, int x, const Info &v) {
        if (l == r) {
            info[id] = v;
            return;
        }
        int mid = l + r >> 1;
        if (x <= mid){
            modify(ls(id), l, mid, x, v);
        } else {
            modify(rs(id), mid + 1, r, x, v);
        }
        pushUp(id);
    }
    void modify(int x, const Info &v) {
        modify(1, 1, n, x, v);        
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if (x > r || y < l) {
            return Info();
        }
        if (x <= l && y >= r) {
            return info[id];
        }
        int mid = l + r >> 1;
        return rangeQuery(ls(id), l, mid, x, y) + rangeQuery(rs(id), mid + 1, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }
    #undef ls
    #undef rs
};