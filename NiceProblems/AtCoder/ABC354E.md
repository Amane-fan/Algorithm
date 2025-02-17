> 题目链接：https://atcoder.jp/contests/abc354/tasks/abc354_e

> 标签：状压dp，博弈论

## 思路：

注意到，决定每次先手能否必胜的条件之和当前剩下的牌有关。

因此，使用状态压缩的方式存储每个牌是否选过，使用状压dp解决。

- 如果当前状态没有任何牌，则当前状态一定是必败态
- 如果当前状态是**必胜态**，那么**至少有一个后继状态是必败态**
- 如果当前状态是**必败态**，那么**所有后继状态一定都是必胜态**

> 注：这里说的必胜以及必败都是对于当前状态，先手而言的

那么对于每一个状态，我们可以暴力枚举选哪两张牌，如果这两张牌满足要求，就往下递归。

如果没有任何两张牌满足要求，那么就是必败态。

时间复杂度： $O(2^{n}\times n^{2})$ 

## Code:

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
    	cin >> a[i].fi >> a[i].se;
    }

    auto check = [&](int i, int j) -> bool {
    	return (a[i].fi == a[j].fi) || (a[i].se == a[j].se);
    };

    int m = (1 << n) - 1;
    vector<int> dp(m + 1, -1);

    auto dfs = [&](auto &&dfs, int mask) -> bool {
    	if (mask == 0) {
    		return false;
    	}
    	if (dp[mask] != -1) return dp[mask];
    	bool res = false;
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < i; j++) {
    			if ((mask >> i & 1) && (mask >> j & 1) && check(i, j)) {
    				res |= !dfs(dfs, mask ^ (1 << i) ^ (1 << j));
    			}
    		}
    	}
    	dp[mask] = res;
    	return res;
    };

    bool ans = dfs(dfs, m);
    cout << (ans ? "Takahashi" : "Aoki") << '\n';
    return 0;
}
```

