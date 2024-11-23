> 题目链接：https://atcoder.jp/contests/abc376/tasks/abc376_e

> 标签：排序，枚举，前 k 大

## 思路：

观察发现，对于数组 A 只需要知道一个值即可，所以我们或许可以先锁定所选元素中，A的最大值，如果能够快速的获取出 B 数组中的最小 k - 1 项和，那么答案就显而易见了。

所以，我们可以先将数组按照 A 从小到大进行排序，这样一来，就可以从左到右枚举 A 中的最大元素。

接下来，我们只需要聚焦 B 数组中的元素，使得他们的和最小即可，由于我们已经选择了第 i 项元素，所以 B 数组中的第 i 项元素也要选，再者，我们规定了 Ai 作为最大值，所以我们只能在 i 前面再寻找 k - 1 项元素，凑成答案即可。

所以，在每次的枚举中，以 Ai 作为最大值的结果最小为 ： **Ai * (前 k - 1 小的 B 中元素 + Bi)**

维护前 k - 1 小的元素可以使用 **std::multiset** 维护 ,同时需要动态维护multiset中的元素和为sum

那么答案即为:  **min(a[i] * (sum + b[i])) (1 <= i <= n)**



## Code：

```cpp
void solve() {
    int n,k;
    cin >> n >> k;
    vector<pair<int,int>> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].fi;
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i].se;
    }
    sort(all(p));
    multiset<int> kth;
    ll ans = 1E18;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        //需要枚举到第 k 个元素才能开始记录答案
        if (sz(kth) < k - 1) {
            kth.insert(p[i].se);
            sum += p[i].se;
            continue;
        }
        ans = min(ans, 1LL * p[i].fi * (sum +  p[i].se));
        //注意 k = 1 的情况，multiset中不需要维护ren
        if (!kth.empty() && p[i].se < *kth.rbegin()) {
            sum -= *kth.rbegin();
            kth.erase(prev(kth.end()));
            kth.insert(p[i].se);
            sum += p[i].se;
        }
    }
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

