const int N = 5e5 + 10;
int a[N],n;

#define sum(x) d[x].sum
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
struct Node{
    ll sum;
}d[N << 2];

void pushUp(int cur) {
    sum(cur) = sum(ls(cur)) + sum(rs(cur));
}

void build(int cur = 1,int l = 1,int r = n) {
    if (l == r) {
        sum(cur) = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls(cur),l,mid);
    build(rs(cur),mid + 1,r);
    pushUp(cur);
};

void add(int pos,int val,int cur = 1,int l = 1,int r = n) {
    if (l == r) {
        sum(cur) += val;
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid) add(pos,val,ls(cur),l,mid);
    else add(pos,val,rs(cur),mid + 1,r);
    pushUp(cur);
}

ll query(int ql,int qr,int cur = 1,int l = 1,int r = n) {
    if (ql <= l && qr >= r) return sum(cur);
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query(ql,qr,ls(cur),l,mid);
    if (qr > mid) res += query(ql,qr,rs(cur),mid + 1,r);
    return res;
}