> 题目链接：https://atcoder.jp/contests/abc365/tasks/abc365_e

> 标签：贡献，拆位，异或，推柿子

## 思路：

首先我们可以对该式子进行处理：

### $\sum_{i=1}^{n-1}$ $\sum_{j=i+1}^{n}$ $ai\oplus ai+1\oplus...aj$     =    $\sum_{i=1}^{n}$ $\sum_{j=i}^{n}$ $ai\oplus ai+1\oplus...aj$  $-$ $\sum_{i=1}^{n}ai$

记 `b[i]` = $\sum_{i}^{j}$ $ai\oplus ai+1\oplus...aj$

则上式等于

### $\sum_{i=0}^{n-1}$ $\sum_{j=i+1}^{n}$ $bi\oplus bj  - $ $\sum_{i=1}^{n}ai$

如此一来，我们就可以通过计算每个数的每一位的贡献解决

对于每一个数 `bj` ，我们需要知道前面各个数和当前数异或的结果

考虑拆位，如果当前数的某一位是1，前面已经枚举过的数当前位的 0 的数量是 k ，则代表当前位中，前面有 k 个数和当前数异或会对结果产生贡献

具体操作是：

开一个长为30的数组，用来统计前面已经枚举过的数中，各位的 1 的数量

枚举 `bj` ，并且枚举 `bj` 的每一位，且前面枚举过的数中，当前位的 1 的数量 k，用 cnt 代表前面有多少个数与当前位能产生贡献

如果当前位是0，则 cnt = k，否则，cnt = i - k

那么当前枚举的数的当前位数所产生的贡献就是 `cnt * (1 << bit)` （bit 代表当前的位数）

## Code：

```cpp
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = b[i - 1] ^ a[i];
    }
    array<int,30> f{};
    ll ans = -accumulate(All(a),0LL);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 30; j++) {
            int cnt = 0;
            if (b[i] >> j & 1) cnt = i - f[j];
            else cnt = f[j];
            ans += 1LL * cnt * (1 << j);
            f[j] += b[i] >> j & 1;
        }
    }
    cout << ans << '\n';
    return 0;
}

```

