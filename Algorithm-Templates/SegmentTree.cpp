const int N = 1e5 + 10;
int a[N],n;

#define sum(x) d[x].sum
#define len(x) d[x].len
#define add(x) d[x].add
struct Node{
    ll sum;
    int len;
    ll add;
}d[N << 2];

void tag(int cur,int val) {
    sum(cur) += 1LL * val * len(cur);
    add(cur) += val;
}

void pushDown(int cur) {
    if (add(cur)) {
        tag(ls(cur),add(cur));
        tag(rs(cur),add(cur));
        add(cur) = 0;
    }
}

void pushUp(int cur) {
    sum(cur) = sum(ls(cur)) + sum(rs(cur));
}

void build(int cur = 1,int l = 1,int r = n) {
    len(cur) = r - l + 1;
    if (l == r) {
        sum(cur) = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls(cur),l,mid);
    build(rs(cur),mid + 1,r);
    pushUp(cur);
}

void update(int ql,int qr,int val,int cur = 1,int l = 1,int r = n) {
    if (ql <= l && qr >= r) {
        tag(cur,val);
        return;
    }
    pushDown(cur);
    int mid = l + r >> 1;
    if (ql <= mid) update(ql,qr,val,ls(cur),l,mid);
    if (qr > mid) update(ql,qr,val,rs(cur),mid + 1,r);
    pushUp(cur);
}

ll query(int ql,int qr,int cur = 1,int l = 1,int r = n) {
    if (ql <= l && qr >= r) return sum(cur);
    pushDown(cur);
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query(ql,qr,ls(cur),l,mid);
    if (qr > mid) res += query(ql,qr,rs(cur),mid + 1,r);
    return res;
}