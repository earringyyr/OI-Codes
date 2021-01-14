#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
int n, q;
int a[100005];
struct node
{
    int l;
    int r;
    int minx;
    int maxn;
    ll num;
    int lazy;
} tr[400005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].minx = a[l];
        tr[id].maxn = a[l];
        tr[id].num = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    tr[id].num = tr[lch].num + tr[rch].num;
    return;
}
void pushdown(int id)
{
    int lazy = tr[id].lazy;
    tr[id].lazy = 0;
    tr[lch].minx += lazy;
    tr[lch].maxn += lazy;
    tr[lch].num += (ll)(tr[lch].r - tr[lch].l + 1) * lazy;
    tr[lch].lazy += lazy;
    tr[rch].minx += lazy;
    tr[rch].maxn += lazy;
    tr[rch].num += (ll)(tr[rch].r - tr[rch].l + 1) * lazy;
    tr[rch].lazy += lazy;
    return;
}
void add(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].minx += val;
        tr[id].maxn += val;
        tr[id].num += (ll)(r - l + 1) * val;
        tr[id].lazy += val;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r, val);
    if (l >= mid + 1)
        add(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid, val);
        add(rch, mid + 1, r, val);
    }
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    tr[id].num = tr[lch].num + tr[rch].num;
    return;
}
void change(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        int delta_maxn = tr[id].maxn - floor((double)tr[id].maxn / val);
        int delta_minx = tr[id].minx - floor((double)tr[id].minx / val);
        if (delta_maxn == delta_minx)
        {
            tr[id].minx -= delta_minx;
            tr[id].maxn -= delta_maxn;
            tr[id].num -= (ll)(r - l + 1) * delta_maxn;
            tr[id].lazy -= delta_maxn;
            return;
        }
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        change(lch, l, r, val);
    if (l >= mid + 1)
        change(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        change(lch, l, mid, val);
        change(rch, mid + 1, r, val);
    }
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    tr[id].num = tr[lch].num + tr[rch].num;
    return;
}
int ask_minx(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].minx;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask_minx(lch, l, r);
    if (l >= mid + 1)
        return ask_minx(rch, l, r);
    return min(ask_minx(lch, l, mid), ask_minx(rch, mid + 1, r));
}
ll ask_sum(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask_sum(lch, l, r);
    if (l >= mid + 1)
        return ask_sum(rch, l, r);
    return ask_sum(lch, l, mid) + ask_sum(rch, mid + 1, r);
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= q; ++i)
    {
        int type, l, r;
        scanf("%d%d%d", &type, &l, &r);
        ++l;
        ++r;
        if (type == 1)
        {
            int c;
            scanf("%d", &c);
            add(1, l, r, c);
        }
        else if (type == 2)
        {
            int d;
            scanf("%d", &d);
            change(1, l, r, d);
        }
        else if (type == 3)
            printf("%d\n", ask_minx(1, l, r));
        else
            printf("%lld\n", ask_sum(1, l, r));
    }
    return 0;
}