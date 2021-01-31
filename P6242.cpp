#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
const ll inf = 0x7fffffffffffffff;
int n, m;
int a[500005];
struct tree
{
    int l;
    int r;
    int cnt;
    ll mx1;
    ll mx2;
    ll lz1;
    ll lz2;
    ll maxn;
    ll lazy1;
    ll lazy2;
    ll sum;
} tr[2000005];
void pushdown(int id)
{
    if (tr[lch].mx1 + tr[id].lz1 == tr[id].mx1)
    {
        tr[lch].maxn = max(tr[lch].maxn, tr[lch].mx1 + tr[id].lazy1);
        tr[lch].lazy1 = max(tr[lch].lazy1, tr[lch].lz1 + tr[id].lazy1);
        tr[lch].mx1 += tr[id].lz1;
        tr[lch].lz1 += tr[id].lz1;
        tr[lch].sum += tr[lch].cnt * tr[id].lz1;
    }
    else
    {
        tr[lch].maxn = max(tr[lch].maxn, tr[lch].mx1 + tr[id].lazy2);
        tr[lch].lazy1 = max(tr[lch].lazy1, tr[lch].lz1 + tr[id].lazy2);
        tr[lch].mx1 += tr[id].lz2;
        tr[lch].lz1 += tr[id].lz2;
        tr[lch].sum += tr[lch].cnt * tr[id].lz2;
    }
    if (tr[rch].mx1 + tr[id].lz1 == tr[id].mx1)
    {
        tr[rch].maxn = max(tr[rch].maxn, tr[rch].mx1 + tr[id].lazy1);
        tr[rch].lazy1 = max(tr[rch].lazy1, tr[rch].lz1 + tr[id].lazy1);
        tr[rch].mx1 += tr[id].lz1;
        tr[rch].lz1 += tr[id].lz1;
        tr[rch].sum += tr[rch].cnt * tr[id].lz1;
    }
    else
    {
        tr[rch].maxn = max(tr[rch].maxn, tr[rch].mx1 + tr[id].lazy2);
        tr[rch].lazy1 = max(tr[rch].lazy1, tr[rch].lz1 + tr[id].lazy2);
        tr[rch].mx1 += tr[id].lz2;
        tr[rch].lz1 += tr[id].lz2;
        tr[rch].sum += tr[rch].cnt * tr[id].lz2;
    }
    if (tr[lch].mx2 != -inf)
    {
        tr[lch].lazy2 = max(tr[lch].lazy2, tr[lch].lz2 + tr[id].lazy2);
        tr[lch].mx2 += tr[id].lz2;
        tr[lch].lz2 += tr[id].lz2;
        tr[lch].sum += (tr[lch].r - tr[lch].l + 1 - tr[lch].cnt) * tr[id].lz2;
    }
    if (tr[rch].mx2 != -inf)
    {
        tr[rch].lazy2 = max(tr[rch].lazy2, tr[rch].lz2 + tr[id].lazy2);
        tr[rch].mx2 += tr[id].lz2;
        tr[rch].lz2 += tr[id].lz2;
        tr[rch].sum += (tr[rch].r - tr[rch].l + 1 - tr[rch].cnt) * tr[id].lz2;
    }
    tr[id].lz1 = 0;
    tr[id].lz2 = 0;
    tr[id].lazy1 = 0;
    tr[id].lazy2 = 0;
    return;
}
void pushup(int id)
{
    if (tr[lch].mx1 > tr[rch].mx1)
    {
        tr[id].cnt = tr[lch].cnt;
        tr[id].mx1 = tr[lch].mx1;
        tr[id].mx2 = max(tr[lch].mx2, tr[rch].mx1);
    }
    else if (tr[lch].mx1 < tr[rch].mx1)
    {
        tr[id].cnt = tr[rch].cnt;
        tr[id].mx1 = tr[rch].mx1;
        tr[id].mx2 = max(tr[lch].mx1, tr[rch].mx2);
    }
    else
    {
        tr[id].cnt = tr[lch].cnt + tr[rch].cnt;
        tr[id].mx1 = tr[lch].mx1;
        tr[id].mx2 = max(tr[lch].mx2, tr[rch].mx2);
    }
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].cnt = 1;
        tr[id].mx1 = a[l];
        tr[id].mx2 = -inf;
        tr[id].maxn = a[l];
        tr[id].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    pushup(id);
    return;
}
void add1(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].mx1 += val;
        tr[id].lz1 += val;
        tr[id].lazy1 = max(tr[id].lazy1, tr[id].lz1);
        if (tr[id].mx2 != -inf)
        {
            tr[id].mx2 += val;
            tr[id].lz2 += val;
            tr[id].lazy2 = max(tr[id].lazy2, tr[id].lz2);
        }
        tr[id].maxn = max(tr[id].maxn, tr[id].mx1);
        tr[id].sum += (ll)(tr[id].r - tr[id].l + 1) * val;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add1(lch, l, r, val);
    if (l >= mid + 1)
        add1(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        add1(lch, l, mid, val);
        add1(rch, mid + 1, r, val);
    }
    pushup(id);
    return;
}
void add2(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        if (val >= tr[id].mx1)
            return;
        if (val < tr[id].mx1 && val > tr[id].mx2)
        {
            tr[id].sum -= (tr[id].mx1 - val) * tr[id].cnt;
            tr[id].lz1 -= tr[id].mx1 - val;
            tr[id].mx1 = val;
            return;
        }
        pushdown(id);
        int mid = (tr[id].l + tr[id].r) >> 1;
        add2(lch, l, mid, val);
        add2(rch, mid + 1, r, val);
        pushup(id);
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add2(lch, l, r, val);
    if (l >= mid + 1)
        add2(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        add2(lch, l, mid, val);
        add2(rch, mid + 1, r, val);
    }
    pushup(id);
    return;
}
ll ask3(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].sum;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask3(lch, l, r);
    if (l >= mid + 1)
        return ask3(rch, l, r);
    return ask3(lch, l, mid) + ask3(rch, mid + 1, r);
}
ll ask4(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].mx1;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask4(lch, l, r);
    if (l >= mid + 1)
        return ask4(rch, l, r);
    return max(ask4(lch, l, mid), ask4(rch, mid + 1, r));
}
ll ask5(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].maxn;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask5(lch, l, r);
    if (l >= mid + 1)
        return ask5(rch, l, r);
    return max(ask5(lch, l, mid), ask5(rch, mid + 1, r));
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int type, l, r;
        scanf("%d%d%d", &type, &l, &r);
        if (type == 1)
        {
            int k;
            scanf("%d", &k);
            add1(1, l, r, k);
        }
        else if (type == 2)
        {
            int v;
            scanf("%d", &v);
            add2(1, l, r, v);
        }
        else if (type == 3)
            printf("%lld\n", ask3(1, l, r));
        else if (type == 4)
            printf("%lld\n", ask4(1, l, r));
        else
            printf("%lld\n", ask5(1, l, r));
    }
    return 0;
}