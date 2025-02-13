> 题目链接：https://atcoder.jp/contests/abc389/tasks/abc389_f

> 标签：线段树，二分，dp

# 思路：

对于多组询问，肯定不能对于每一个初始分数暴力求解，发现 $x$ 的上界是 5e5 ，因此考虑将所有 $x$ 预处理出来，对于每组询问直接输出答案。

首先考虑最朴素的dp，使用 $dp_i,_j$ 表示，在打完前 $i$ 场比赛后，初始分数为 $j$ 时，最后的分数。

不难发现，如果第二维固定，那么第一维的转移非常简单

-  $dp_i,_j = dp_{i - 1},_j$ ，当 $dp_{i - 1},_j$ **不在**第 $i$ 场比赛的rating范围内

- $dp_i,_j = dp_{i - 1},_j + 1$ ，当 $dp_{i - 1},_j$ **在**第 $i$ 场比赛的rating范围内

我们考虑将第二维整体转移，做一个类似于滚动 dp 的事情，然后只需要将上一次的 dp 中，在范围内的数全部增加 1 即可。

初始时， $dp_i = i$ ，此时整个 dp 数组是递增并且连续的，将范围内的数全部增加 1 后，得到的数组依然是递增的，只不过有可能变成非严格递增，因此，**得到的每一个数组都是非严格递增的**，由此可以得出，**增加 1 的范围一定是连续的**。

有了上述两个性质，就会发现我们可以用二分找到需要增加 1 的范围的上下界，再将这个区间全部增加 1 ，可以用线段树维护。

使用树上二分的技巧可以让 $log^2$ 变为 $log$ 。

> 注意，使用树上二分的时候，要写的函数优先考虑前缀或者后缀是false的情况，再取反即可。

时间复杂度： $O(N*logN + q*logN)$

# Code:

> 附懒标记线段树及树上二分模板

```c++
#include <bits/stdc++.h>
using namespace std;
#define si(x) int(x.size())
#define all(x) (x).begin(),(x).end()
#define All(x) (x).begin() + 1,(x).end()
#define fi first
#define se second
using ll = long long;
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return true; } return false; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return true; } return false; }

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

constexpr int inf = 1e9;

struct Tag {
    int add;
    Tag(): add(0) {}
    Tag(int add_): add(add_) {}
    void apply(const Tag &t) {
        add += t.add;
    }
};

struct Info {
    int len;
    int mx;
    int mi;
    Info(): mx(-inf), len(0), mi(inf) {}
    Info(int mx_, int mi_): mx(mx_), mi(mi_), len(1) {}
    void apply(const Tag &t) {
        mx += t.add;
        mi += t.add;
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.mx = max(a.mx, b.mx);
    c.mi = min(a.mi, b.mi);
    c.len = a.len + b.len;
    return c;
}

constexpr int N = 5e5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        a[i] = {l, r};
    }

    LazySegmentTree<Info, Tag> seg(N);
    for (int i = 1; i <= N; i++) {
        seg.modify(i, Info(i, i));
    }

    for (int i = 1; i <= n; i++) {
        auto lower = [&](const Info &info) {
            return info.mx >= a[i].fi;
        };

        auto upper = [&](const Info &info) {
            return info.mi <= a[i].se;
        };

        int L = seg.findFirst(1, N, lower);
        int R = seg.findLast(1, N, upper);
        seg.rangeApply(L, R, Tag(1));
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        cout << seg.rangeQuery(x, x).mx << '\n';
    }

    return 0;
}
```

