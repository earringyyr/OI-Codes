#include <iostream>
#include <cstdio>
#define lch id << 1
#define rch id << 1 | 1
#define int long long
using namespace std;
int n, m, a[100005];
struct tree
{
    int l;
    int r;
    int num;
    int lazy;
} tr[400005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].num = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].num = tr[lch].num + tr[rch].num;
    return;
}
void pushdown(int id)
{
    int lazy = tr[id].lazy;
    tr[id].lazy = 0;
    tr[lch].num += lazy * (tr[lch].r - tr[lch].l + 1);
    tr[rch].num += lazy * (tr[rch].r - tr[rch].l + 1);
    tr[lch].lazy += lazy;
    tr[rch].lazy += lazy;
    return;
}
void add(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num += val * (r - l + 1);
        tr[id].lazy += val;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r, val);
    else if (l >= mid + 1)
        add(rch, l, r, val);
    else if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid, val);
        add(rch, mid + 1, r, val);
    }
    tr[id].num = tr[lch].num + tr[rch].num;
    return;
}
int ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    return ask(lch, l, mid) + ask(rch, mid + 1, r);
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int type;
        scanf("%lld", &type);
        if (type == 1)
        {
            int x, y, k;
            scanf("%lld%lld%lld", &x, &y, &k);
            add(1, x, y, k);
        }
        if (type == 2)
        {
            int x, y;
            scanf("%lld%lld", &x, &y);
            printf("%lld\n", ask(1, x, y));
        }
    }
    return 0;
}