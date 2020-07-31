#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, pp, ans = 0x7fffffff, b[1000005];
struct node
{
    int l;
    int r;
} a[500005];
struct tree
{
    int l;
    int r;
    int num;
    int lazy;
} tr[4000005];
bool cmp(node aa, node bb)
{
    return aa.r - aa.l < bb.r - bb.l;
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
        tr[lch].num += lazy;
        tr[rch].num += lazy;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
    }
    return;
}
void add(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num += val;
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
    tr[id].num = max(tr[lch].num, tr[rch].num);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].l, &a[i].r);
        b[2 * i - 1] = a[i].l;
        b[2 * i] = a[i].r;
    }
    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + 2 * n + 1);
    int len = unique(b + 1, b + 2 * n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
    {
        a[i].l = lower_bound(b + 1, b + len + 1, a[i].l) - b;
        a[i].r = lower_bound(b + 1, b + len + 1, a[i].r) - b;
    }
    build(1, 1, len);
    int l = 1;
    for (int i = 1; i <= n; ++i)
    {
        int p = 0;
        add(1, a[i].l, a[i].r, 1);
        while (l < i && tr[1].num >= m)
        {
            p = 1;
            add(1, a[l].l, a[l].r, -1);
            ++l;
        }
        if (p)
        {
            pp = 1;
            ans = min(ans, (b[a[i].r] - b[a[i].l]) - (b[a[l - 1].r] - b[a[l - 1].l]));
        }
    }
    if (pp)
        printf("%d", ans);
    else
        printf("-1");
    return 0;
}