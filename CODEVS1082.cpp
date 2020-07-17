#include <iostream>
#include <cstdio>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
long long n, q, a[200005];
struct tree
{
    long long l;
    long long r;
    long long sum;
    long long lazy;
} tr[800005];
void build(long long id, long long l, long long r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (tr[id].l == tr[id].r)
    {
        tr[id].sum = a[l];
        return;
    }
    long long mid = (tr[id].l + tr[id].r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
void pushdown(long long id)
{
    if (tr[id].l != tr[id].r)
    {
        tr[lch].lazy += tr[id].lazy;
        tr[rch].lazy += tr[id].lazy;
        tr[lch].sum += tr[id].lazy * (tr[lch].r - tr[lch].l + 1);
        tr[rch].sum += tr[id].lazy * (tr[rch].r - tr[rch].l + 1);
        tr[id].lazy = 0;
    }
    return;
}
void add(long long id, long long l, long long r, long long val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].lazy += val;
        tr[id].sum += val * (tr[id].r - tr[id].l + 1);
        return;
    }
    long long mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r, val);
    if (l >= mid + 1)
        add(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid, val);
        add(rch, mid + 1, r, val);
    }
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
long long ask(long long id, long long l, long long r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].sum;
    long long mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return ask(lch, l, mid) + ask(rch, mid + 1, r);
}
int main()
{
    scanf("%lld", &n);
    for (long long i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    build(1, 1, n);
    scanf("%lld", &q);
    for (long long i = 1; i <= q; ++i)
    {
        long long type;
        scanf("%lld", &type);
        if (type == 1)
        {
            long long x, y, w;
            scanf("%lld%lld%lld", &x, &y, &w);
            add(1, x, y, w);
        }
        else
        {
            long long x, y;
            scanf("%lld%lld", &x, &y);
            printf("%lld\n", ask(1, x, y));
        }
    }
    return 0;
}