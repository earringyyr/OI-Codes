#include <iostream>
#include <cstdio>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int t, n, a[50005];
struct tree
{
    int l;
    int r;
    int sum;
} tr[200005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
void add(int id, int w, int val)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].sum += val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w, val);
    else
        add(rch, w, val);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
int query(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].sum;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return query(lch, l, mid) + query(rch, mid + 1, r);
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        printf("Case %d:\n", tt);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        build(1, 1, n);
        string type;
        while (cin >> type)
        {
            if (type == "End")
                break;
            int x, y;
            scanf("%d%d", &x, &y);
            if (type == "Add")
                add(1, x, y);
            if (type == "Sub")
                add(1, x, -y);
            if (type == "Query")
                printf("%d\n", query(1, x, y));
        }
    }
    return 0;
}