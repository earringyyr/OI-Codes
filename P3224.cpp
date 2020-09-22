#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, q, cnt, p[100005], id[100005], rt[100005], fa[100005];
struct tree
{
    int l;
    int r;
    int num;
    int ans;
} tr[5100005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void pushup(int x)
{
    tr[x].num = tr[tr[x].l].num + tr[tr[x].r].num;
    return;
}
void add(int &x, int l, int r, int w)
{
    if (!x)
        x = ++cnt;
    if (l == r)
    {
        ++tr[x].num;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[x].l, l, mid, w);
    else
        add(tr[x].r, mid + 1, r, w);
    pushup(x);
    return;
}
int merge(int x, int y, int l, int r)
{
    if (!x || !y)
        return x | y;
    if (l == r)
    {
        tr[x].num += tr[y].num;
        return x;
    }
    int mid = (l + r) >> 1;
    tr[x].l = merge(tr[x].l, tr[y].l, l, mid);
    tr[x].r = merge(tr[x].r, tr[y].r, mid + 1, r);
    pushup(x);
    return x;
}
int query(int x, int l, int r, int w)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (tr[tr[x].l].num >= w)
        return query(tr[x].l, l, mid, w);
    else
        return query(tr[x].r, mid + 1, r, w - tr[tr[x].l].num);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        scanf("%d", &p[i]);
        id[p[i]] = i;
        add(rt[i], 1, 300005, p[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u = getfather(u);
        v = getfather(v);
        if (u != v)
        {
            fa[u] = v;
            rt[v] = merge(rt[u], rt[v], 1, 300005);
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        char op;
        int x, y;
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'Q')
        {
            x = getfather(x);
            if (y > tr[rt[x]].num)
                puts("-1");
            else
                printf("%d\n", id[query(rt[x], 1, 300005, y)]);
        }
        else
        {
            x = getfather(x);
            y = getfather(y);
            if (x != y)
            {
                fa[x] = y;
                rt[y] = merge(rt[x], rt[y], 1, 300005);
            }
        }
    }
    return 0;
}