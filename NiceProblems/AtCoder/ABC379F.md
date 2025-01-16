> 题目链接：https://atcoder.jp/contests/abc379/tasks/abc379_f

> 标签：ST表，单调栈，二分

## 思路：

首先思考一个问题，如果询问只有 $r$ ，那么可以由单调栈轻松解决，答案即为单调栈中元素的个数

但是题目中加了一个 $l$ 的限制，注意到，如果在 $l$ 位置能够看到，则 $R$ 位置也一定能够看到。也就是说， $l$ 能看到的一定是 $r$ 能看到的数的子集。

给出一个简单的**证明**：假设 $x$ 是 $r$ 能看到的某一个位置，那么一定满足 $\max_{a[r + 1]}^{a[x - 1]} < a[x]$ ，但是如果要满足 $l$ 位置也能够看到，那么还需要满足 $max_{a[l + 1]}^{a[x - 1]} < a[x]$ （包括了上一个式子的区间） ，也就是说， $l$ 位置要能够看到，要求更加严格，需要在 $r$ 位置能够看到的数中取子集。

根据上述两个式子，如果 $l和r$ 都要满足要求，只需要在满足 $r$ 的要求基础上，再满足 $max_{a[l + 1]}^{a[r]} < a[x]$ 

发现 $r$ 位置满足要求的数一定都在单调栈中，那么我们只需要在这里面去寻找满足 $l$ 位置的即可。由于单调栈里面的元素是有序的，所以可以通过二分去寻找。

综上，我们只需要将所有询问离线下来，按照区间右端点降序排序，就可以使用单调栈进行维护。

对于每组询问的区间最值，用 ST表或者线段树维护。

时间复杂度： $O(nlogn)$

## Code:

```c++
#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define All(x) (x).begin() + 1,(x).end()
#define fi first
#define se second
using ull = unsigned long long;
using ll = long long;
using F = long double;
using namespace std;

/*   /\_/\
*   (= ._.)
*   / >  \>
*/

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


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SparseTable ST(a, [&](int a, int b) {
        return max(a, b);
    });

    vector<array<int,3>> Q(q);
    for (int i = 0; i < q; i++) {
        int l,r;
        cin >> l >> r;
        Q[i] = {i, l, r};
    }

    sort(all(Q), [&](auto &a, auto &b) {
        return a[2] > b[2];
    });

    vector<int> stk;
    vector<int> ans(q);

    auto find = [&](int x) -> int {
        int lo = 0, hi = sz(stk) - 1;
        while (lo <= hi) {
            int mid = lo + hi >> 1;
            if (stk[mid] > x) lo = mid + 1;
            else hi = mid - 1;
        }
        return hi + 1;
    };

    int j = 0; // 询问索引
    for (int i = n; i >= 1; i--) {
        while (j < q && Q[j][2] == i) {
            auto [id, l, r] = Q[j];
            auto mx = ST.query(l + 1, r);
            int cnt = find(mx);
            ans[id] = cnt;
            j++;
        }
        while (!stk.empty() && a[i] >= stk.back()) stk.pop_back();
        stk.push_back(a[i]);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
```

