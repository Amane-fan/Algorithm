template <class Info, class Tag>
struct LazySegmentTree {
    #define ls(x) (x << 1)
    #define rs(x) (x << 1 | 1)
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree(): n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(vector<Info>(n_ + 1, v_));
    }
    LazySegmentTree(vector<Info> init_) {
        init(init_);
    }
    void init(vector<Info> init_) {
        n = init_.size() - 1;
        info.assign(n << 2, Info());
        tag.assign(n << 2, Tag());
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
    void apply(int id, const Tag &t) {
        info[id].apply(t);
        tag[id].apply(t);
    }
    void pushDown(int id) {
        apply(ls(id), tag[id]);
        apply(rs(id), tag[id]);
        tag[id] = Tag();
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
        pushDown(id);
        int mid = l + r >> 1;
        return rangeQuery(ls(id), l, mid, x, y) + rangeQuery(rs(id), mid + 1, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }
    void rangeApply(int id, int l, int r, int x, int y, const Tag &t) {
        if (x > r || y < l) {
            return;
        }
        if (x <= l && y >= r) {
            apply(id, t);
            return;
        }
        pushDown(id);
        int mid = l + r >> 1;
        rangeApply(ls(id), l, mid, x, y, t);
        rangeApply(rs(id), mid + 1, r, x, y, t);
        pushUp(id);
    }
    void rangeApply(int l, int r, const Tag &t) {
        rangeApply(1, 1, n, l, r, t);
    }
    template<class F>
    int findFirst(int id, int l, int r, int x, int y, F &&pred) {
        if (x > r || y < l) {
            return -1;
        }
        if (x <= l && y >= r && !pred(info[id])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        pushDown(id);
        int mid = l + r >> 1;
        int res = findFirst(ls(id), l, mid, x, y, pred);
        if (res == -1) {
            res = findFirst(rs(id), mid + 1, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 1, n, l, r, pred);
    }
    template<class F>
    int findLast(int id, int l, int r, int x, int y, F &&pred) {
        if (x > r || y < l) {
            return -1;
        }
        if (x <= l && y >= r && !pred(info[id])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        pushDown(id);
        int mid = l + r >> 1;
        int res = findLast(rs(id), mid + 1, r, x, y, pred);
        if (res == -1) {
            res = findLast(ls(id), l, mid, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 1, n, l, r, pred);
    }
    #undef ls
    #undef rs
};
