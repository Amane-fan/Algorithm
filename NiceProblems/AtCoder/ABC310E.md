> 题目链接：https://atcoder.jp/contests/abc310/tasks/abc310_e

> 标签：DP，位运算

## 思路：

注意到，本题的题意就是让我们求出二维矩阵 $f$ 的上三角和

### 状态表示：

题目已经给出其递推公式，发现：每一列的数据都可以由前一列以及当前列的最后一个元素（也就是 $A_i$ ）得出，因此，考虑使用 $dp_i$ 来表示第 $i$ 列的和，但是为了表示方便，可以采用 $dp_i,_j$ 表示第 $i$ 列中，$j$ 的个数，易得： $dp_i,_0 + dp_i,_1 = i$ 

### 初始化：

当 $A_i = 1$ 时， $dp_1,_1 = 1$

当 $A_i = 0$ 是， $dp_1,_0 = 1$

### 状态转移方程：

 首先分类讨论：

- 当 $A_i = 1$ 时， 考虑到左边那一列都会和 $A_i$ 进行二元运算，根据定义只有0和0运算才能得到1，因此这一列中 1 的数量等于左边一列中的 0 的数量再加上本身的1， 也就是 $dp_i,_1 = dp_{i - 1},_0 + 1$ ，所以 $dp_i,_0 = i - dp_1,_1$ 

- 当 $A_i = 0$ 时，无论前一列取什么值，当前列的所有值（除了 $f_i,_i$ 本身）都一定等于 1 

  因此， $dp_i,_0 = 1$ ，所以 $dp_i,_1 = i - 1$ 

最后的答案 $ans = \sum_{i = 1}^{n}dp_i,_1$ 

## Code:

```c++
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n >> s;
    s = " " + s;
    vector<array<int,2>> dp(n + 1, array<int,2>{});

    dp[1][s[1] == '1'] = 1;
    ll ans = dp[1][1];
    for (int i = 2; i <= n; i++) {
        if (s[i] == '1') {
            dp[i][1] = dp[i - 1][0] + 1;
            dp[i][0] = i - dp[i][1];
        } else {
            dp[i][0] = 1;
            dp[i][1] = i - 1;
        }
        ans += dp[i][1];
    }
    cout << ans << '\n';
    return 0;
}
```



