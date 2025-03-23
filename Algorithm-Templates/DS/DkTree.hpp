// 以小根堆为例
// 三条性质：
// 1：对于树上的一条深度单调递增的路径，其权值单调不减
// 2：笛卡尔树中任意一个完整的子树的节点集合在原数组中连续
// 3：对于任意两点u，v，其lca的权值一定是原数组中[u,v]的最小值

vector<int> stk;
vector<int> lc(n + 1), rc(n + 1);
for (int i = 1; i <= n; i++) {
    while (!stk.empty() && a[i] < a[stk.back()]) {
        lc[i] = stk.back();
        stk.pop_back();
    }
    if (!stk.empty()) {
        rc[stk.back()] = i;
    }
    stk.push_back(i);
}
