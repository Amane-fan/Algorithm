> 题目链接：https://atcoder.jp/contests/abc380/tasks/abc380_e

> 标签：并查集

## 思路：

思考一下，如果在每次的 1 操作的同时，能够快速获取到 x 能够到达的元素数量，那么我们就能够动态更新出各种颜色的元素数量

具体地说：x 所在元素集合的数量是 k ，那么我们只需要将 x 原来所在颜色的数量 - k，同时，让 c 颜色的数量 +k 即可。

或许**并查集**可以做到。

并查集可以支持各种元素所在集合的合并，同时维护各个集合的数量，满足我需要的要求，但是，在每次 1 操作的时候，如何知道有哪些元素会跟 x 所在集合并呢？

根据题意，x元素能够到达的元素只能与 x 相邻，并且颜色要与 x 相同。（赛时读错题了，以为只需要颜色相同就行QAQ）

我们可以另外开一个数组col，代表各个元素集合的颜色是什么，将相同颜色的元素放进一个集合里面

那么能与 x 元素合并的，不就**只能是 x 集合左右相邻并且颜色相同的集合**吗？并且还能够得到一个显然信息，**所有元素的所在集合一定是连续的**。

那么还剩下最后一个问题，我如何知道 x 所在集合的左边元素和右边元素是谁呢？

这就可以使用并查集维护各个集合的最小元素和最大元素，得到最小和最大元素，那么其左边和右边的元素也就显而易见了。

所以我们的具体操作就出来了，每次执行 1 操作时，先将各个颜色的数量进行更新，也就是我开头说的那样，然后找到 l 和 r 分别代表 x 所在集合左边和右边的元素，依次判断其需不需要和 x 集合合并，如果需要合并，则需要动态维护集合的最小值，最大值以及元素数量。

最后进行 2 操作的时候只需要直接输出 c 颜色的数量即可。

## Code：

> 附并查集模板

```cpp
struct DSU {
    std::vector<int> p,cnt;
    DSU(){}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        p.resize(n);
        std::iota(p.begin(),p.end(),0);
        cnt.assign(n,1);
    }
    int find(int x) {
        if (x != p[x]) {
            p[x] = find(p[x]);
        }
        return p[x];
    }
    bool merge(int x,int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        cnt[x] += cnt[y];
        p[y] = x;
        return true;
    }
    int size(int x) {
        return cnt[find(x)];
    }
    bool same(int x,int y) {
        return find(x) == find(y);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);    
    int n,q;
    cin >> n >> q;
    // col[i] 表示以 i 为代表元的所在集合的颜色
    // mx[i] 表示以 i 为代表元的所在集合的最大元素，mi同理
    // ans[i] 代表颜色 i 的数量
    vector<int> col(n + 1),mx(n + 1),mi(n + 1),ans(n + 1,1);
    std::iota(all(mx),0);
    std::iota(all(mi),0);
    std::iota(all(col),0);
    DSU dsu(n + 1);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x,c;
            cin >> x >> c;
            int p = dsu.find(x);
            // l 和 r 代表 x 所在集合的左右两边的元素
            int l = mi[p] - 1, r = mx[p] + 1;
            //先将x所在集合的初始颜色数量减去，再将c颜色的数量增加(颜色数量转移)
            ans[col[p]] -= dsu.size(x);
            ans[c] += dsu.size(x);
            //将x集合的颜色变为c
            col[p] = c;
            //判断左边元素颜色是否是c
            if (l >= 1 && col[p] == col[dsu.find(l)]) {
                // 维护合并集合后的mi
                mi[p] = min(mi[p], mi[dsu.find(l)]);
                // 合并左边和中间集合
                dsu.merge(x,l);
            }
            if (r <= n && col[p] == col[dsu.find(r)]) {
                mx[p] = max(mx[p], mx[dsu.find(r)]);
                dsu.merge(x,r);
            }
        }else {
            int c;
            cin >> c;
            cout << ans[c] << '\n';
        }
    }
    return 0;
}
```

