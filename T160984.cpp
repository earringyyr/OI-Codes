#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
const int inf = 0x7ffffff;
int n, q, ans;
int s[200005];
struct node
{
    int l;
    int r;
} a[200005];
struct tree
{
    int l;
    int r;
    int minx;
} tr[800005];
bool cmp(node aa, node bb)
{
    return aa.l < bb.l;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        if (l == 0)
            tr[id].minx = 0;
        else
            tr[id].minx = inf;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    return;
}
void add(int id, int w, int val)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].minx = min(tr[id].minx, val);
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w, val);
    else
        add(rch, w, val);
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    return;
}
int ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].minx;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    return min(ask(lch, l, mid), ask(rch, mid + 1, r));
}
int main()
{
    scanf("%d", &n);
    ans = n;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &s[i]);
        if (!s[i])
        {
            --ans;
            s[i] = -1;
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
        scanf("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + q + 1, cmp);
    build(1, 0, n);
    int j = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (j <= q && a[j].l == i)
        {
            add(1, a[j].r, ask(1, i - 1, a[j].r));
            ++j;
        }
        add(1, i, ask(1, i - 1, i - 1) + s[i]);
    }
    printf("%d", ans - ask(1, n, n));
    return 0;
}