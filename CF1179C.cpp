#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, m, q;
int a[300005], b[300005];
multiset<int, greater<int> > s;
struct tree
{
    int l;
    int r;
    int maxn;
    int lazy;
} tr[4000005];
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
    int lazy = tr[id].lazy;
    tr[id].lazy = 0;
    tr[lch].maxn += lazy;
    tr[lch].lazy += lazy;
    tr[rch].maxn += lazy;
    tr[rch].lazy += lazy;
    return;
}
void add(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].maxn += val;
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
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    return;
}
int ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].maxn;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    return max(ask(lch, l, mid), ask(rch, mid + 1, r));
}
int main()
{
    scanf("%d%d", &n, &m);
    build(1, 1, 1000000);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        add(1, 1, a[i], 1);
        s.insert(a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &b[i]);
        add(1, 1, b[i], -1);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int type, pos, x;
        scanf("%d%d%d", &type, &pos, &x);
        if (type == 1)
        {
            add(1, 1, a[pos], -1);
            s.erase(s.find(a[pos]));
            a[pos] = x;
            add(1, 1, a[pos], 1);
            s.insert(a[pos]);
        }
        else
        {
            add(1, 1, b[pos], 1);
            b[pos] = x;
            add(1, 1, b[pos], -1);
        }
        int lef = 0, rig = 1000000;
        while (lef < rig)
        {
            int mid = (lef + rig + 1) >> 1;
            if (ask(1, mid, 1000000) > 0)
                lef = mid;
            else
                rig = mid - 1;
        }
        if (lef == 0)
            puts("-1");
        else
            printf("%d\n", *s.lower_bound(lef));
    }
    return 0;
}