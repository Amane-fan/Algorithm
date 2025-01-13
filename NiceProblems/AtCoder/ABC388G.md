> 题目链接：https://atcoder.jp/contests/abc388/tasks/abc388_g

> 标签：ST表，二分，贪心

## 思路：

首先考虑如果区间询问是 $[1,n]$ 如何做：

发现答案是单调的，考虑二分答案，对于每一个 $mid$ ，一定是区间 $[1,mid]$ 和区间 $[n - mid + 1, n]$ 从左往右依次配对

简单证明一下：假设 $x1<x2$ 且本应与他们配对的分别是 $y1<y2$ ，如果此时是可以配对成功的，我们选择了 $x1与y2$ 配对，那么就会导致有可能 $x2和y1$ 无法完成配对。因此，无论在哪种情况下，都一定是从左往右依次配对。

那么问题来到了如何针对不同区间询问，如果仍然采用上述方式，那么时间复杂度就是 $O(q*n*logn)$ 无法接受，因此考虑如何优化其中的 $O(n)$ 判断过程。

构造一个序列 $C_i$ 满足如下条件：

- $C_1=inf$ （代表没有满足要求的索引）
- 对于所有 $i$ 满足： $C_i$ 是第 $i$ 个数可以与前面的数配对的最大索引的位置

> 记与 $i$ 位置前面与其配对的数的索引为 $j$ ，那么有： $i = r - k + 1 + x - l$ ，即 $j = i - len + k$ （len代表区间长度） 

 对于区间 $[n - k + 1,n]$ 中的每一个 $i$ 满足： $C_i >= j$ 即 $C_i >= i - len + k$ 。

 即 $C_i - i >= k - len$ 。

发现 $k - len$ 是常数，要满足所有 $i$ 都要大于等于这个常数，那么只需要其中的最小值大于等于它即可。

因此，我们需要一个数据结构，能够快速查询到区间最值：ST表。

我们使用ST表来维护 $C_i - i$ 的最小值，时间复杂度为： $O(1)$ 。

 因此，总的时间复杂度为 $O((n + q)*logn)$ 。

## Code:

> 附ST表模板

```c++
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define All(x) (x).begin() + 1,(x).end()
using ll = long long;
using namespace std;

template <typename T, typename F>
struct SparseTable {
    int n;
    F fun;
    vector<vector<T>> f;
    SparseTable(const vector<T> &a, const F &fun_): n(sz(a) - 1), fun(fun_) {
        int logN = __lg(n) + 1;
        f.assign(n + 1, vector<T>(logN + 1));
        for (int i = 1; i <= n; i++) {
            f[i][0] = a[i];
        }
        for (int j = 1; j <= logN; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[i][j] = fun(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T query(int l, int r) {
        assert(1 <= l && l <= r && r <= n);
        int s = __lg(r - l + 1);
        return fun(f[l][s], f[r - (1 << s) + 1][s]);
    }
};

constexpr int inf = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> c(n + 1, inf);
    for (int i = 2; i <= n; i++) {
        int idx = upper_bound(All(a), a[i] / 2) - a.begin() - 1;
        c[i] = idx - i;
    }

    SparseTable ST(c, [&](int a, int b) {
        return min(a, b);
    });

    int q;
    cin >> q;
    while (q--) {
        int l,r;
        cin >> l >> r;
        int len = r - l + 1;

        auto check = [&](int k) -> bool {
            if (k == 0) return true;
            return ST.query(r - k + 1, r) >= k - len;
        };

        int lo = 0, hi = len / 2;
        while (lo <= hi) {
            int mid = lo + hi >> 1;
            if (check(mid)) lo = mid + 1;
            else hi = mid - 1;
        }
        cout << hi << '\n';
    }
    return 0;
}
```

