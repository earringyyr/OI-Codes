#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
#define int long long
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    return x * f;
}
int n, b[200005];
struct node
{
    int a;
    int b;
    int w;
} a[100005];
struct tree
{
    int l;
    int r;
    int sum;
    int lazy;
} tr[800005];
bool cmp(node aa, node bb)
{
    return aa.a + aa.b < bb.a + bb.b;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        int lazy = tr[id].lazy;
        tr[id].lazy = 0;
        tr[lch].sum += lazy;
        tr[rch].sum += lazy;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
    }
    return;
}
void change(int id, int w, int val)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
    {
        tr[id].sum = max(tr[id].sum, val);
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        change(lch, w, val);
    else
        change(rch, w, val);
    tr[id].sum = max(tr[lch].sum, tr[rch].sum);
    return;
}
void add(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].sum += val;
        tr[id].lazy += val;
        return;
    }
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
    tr[id].sum = max(tr[lch].sum, tr[rch].sum);
    return;
}
int query(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].sum;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return max(query(lch, l, mid), query(rch, mid + 1, r));
}
signed main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i].a = read();
        a[i].b = read();
        a[i].w = read();
        b[2 * i - 1] = a[i].a;
        b[2 * i] = a[i].b;
    }
    sort(b + 1, b + 2 * n + 1);
    int len = unique(b + 1, b + 2 * n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
    {
        a[i].a = lower_bound(b + 1, b + len + 1, a[i].a) - b;
        a[i].b = lower_bound(b + 1, b + len + 1, a[i].b) - b;
    }
    sort(a + 1, a + n + 1, cmp);
    build(1, 1, len);
    for (int i = 1; i <= n; ++i)
    {
        change(1, a[i].a, query(1, 1, min(a[i].a, a[i].b)) + a[i].w);
        if (a[i].b > a[i].a)
            add(1, a[i].a + 1, a[i].b, a[i].w);
    }
    printf("%lld", query(1, 1, len));
    return 0;
}