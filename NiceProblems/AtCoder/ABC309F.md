> 题目链接：https://atcoder.jp/contests/abc309/tasks/abc309_f

> 标签：线段树，离散化，二分，三维偏序

## 思路：

考虑到盒子是可以任意转动的，所以我们将其长宽高排序，小的和小的匹配，大的和大的匹配。

如果我们将第一维升序排序，枚举 $i$ ，我们据需要知道在前面已经枚举的二三维数对中，有没有和当前数对是匹配的。

思考一下，如果我们知道了前面所有**第二维所对应的第三维的最小值**，那么只需要**找在所有小于当前数对的第二维所对应的第三维**小于当前的第三维，如果有，则直接输出Yes即可。

所以我们需要的数据结构需要支持：单点修改，区间查询最小值。可以用线段树维护。

将第二维作为索引，第三维作为值（最小），离散化一下即可。

> 这个思路与 $CF2042D$ 相似。

但是有一个细节需要注意，我们在枚举所有数对的过程中，并不是每次都需要更新。

例如：1 1 2 ，1 2 4 这组数据，如果我们在第一次就更新，就会导致第一维相同，这并不是我们所期望的。

因此，我们需要在第一维相同的子数组的末尾处，再进行统一更新操作，如果遍历到的不是末尾，只需要将其加入到 $tmp$ 数组当中，再次遍历这个数组，依次更新，然后**清空数组**。

注意到统一更新的操作总共不会超过 $n$ 次，所以不会超时。

时间复杂度： $O(nlogn)$

## Code:

```c++
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;

template <class Info>
struct SegmentTree {
    #define ls(x) (x << 1)
    #define rs(x) (x << 1 | 1)
    int n;
    vector<Info> info;
    SegmentTree(): n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector<Info>(n_ + 1, v_));
    }
    template <class T>
    void init(vector<T> init_) {
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
        if (x <= mid) modify(ls(id), l, mid, x, v);
        else modify(rs(id), mid + 1, r, x, v);
        pushUp(id);
    }
    void modify(int x, const Info &v) {
        modify(1, 1, n, x, v);
    }
    Info query(int id, int l, int r, int x, int y) {
        if (x > r || y < l) return Info();
        if (x <= l && y >= r) {
            return info[id];
        }
        int mid = l + r >> 1;
        return query(ls(id), l, mid, x, y) + query(rs(id), mid + 1, r, x, y);
    }
    Info query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    #undef ls
    #undef rs
};

constexpr int inf = 1e9 + 10;

struct Info {
    int z;
    Info(): z(inf) {}
    Info(int z_): z(z_) {}
};

Info operator+(const Info& a, const Info& b) {
    return Info(min(a.z, b.z));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<int,3>> a(n + 1);
    vector<int> sp;
    for (int i = 1; i <= n; i++) {
        array<int,3> f{};
        for (int j = 0; j < 3; j++) {
            cin >> f[j];
        }
        sort(all(f));
        a[i] = f;
        sp.push_back(f[1]);
    }

    sort(all(a),[&](const auto& A, const auto& B) {
        return A[0] < B[0];
    });

    sort(all(sp));
    sp.erase(unique(all(sp)), sp.end());
    int m = sp.size();

    auto find = [&](int x) -> int {
        int res = lower_bound(all(sp), x) - sp.begin() + 1;
        return res;
    };

    SegmentTree<Info> seg(m);
    vector<bool> f(n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i][0] != a[i - 1][0]) f[i - 1] = true;
    }
    f[n] = true;
    vector<int> tmp;

    auto update = [&]() -> void {
        for (auto i : tmp) {
            int k = find(a[i][1]);
            auto info = seg.query(k, k);
            auto newInfo = Info(min(info.z, a[i][2]));
            seg.modify(k, newInfo);
        }
        tmp.clear();
    };

    int pre = inf;
    for (int i = 1; i <= n; i++) {
        int k = find(a[i][1]);
        if (k != 1) {
            auto info = seg.query(1, k - 1);
            if (info.z < a[i][2]) {
                cout << "Yes\n";
                return 0;
            }
        }
        tmp.push_back(i);
        if (f[i]) update();
    }
    cout << "No\n";
    return 0;
}
```

[****]()
