#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
const int inf = 0x7fffffff;
int n, m, cnt, tot, sum, head[4005];
int fa[4005], son[4005], siz[4005];
int dep[4005], dis[4005], dfn[4005];
int top[4005];
struct edge
{
    int u;
    int v;
    int dis;
} q[100005];
struct node
{
    int v;
    int w;
    int nxt;
} a[200005];
struct tree
{
    int l;
    int r;
    int num;
    int lazy;
} tr[8005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int f)
{
    fa[k] = f;
    son[k] = -1;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dis[a[d].v] = dis[k] + a[d].w;
            dep[a[d].v] = dep[k] + 1;
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int topf)
{
    top[k] = topf;
    dfn[k] = ++cnt;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k] && a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].lazy = inf;
    if (l == r)
    {
        tr[id].num = inf;
        return;
    }
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
        tr[id].lazy = inf;
        tr[lch].lazy = min(tr[lch].lazy, lazy);
        tr[rch].lazy = min(tr[rch].lazy, lazy);
        tr[lch].num = min(tr[lch].num, lazy);
        tr[rch].num = min(tr[rch].num, lazy);
    }
    return;
}
void add(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num = min(tr[id].num, val);
        tr[id].lazy = val;
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
    return;
}
int query(int id, int pos)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
        return tr[id].num;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (pos <= mid)
        return query(lch, pos);
    else
        return query(rch, pos);
}
int lca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    return u;
}
void change(int u, int v, int val)
{
    while (u != v)
    {
        if (top[u] == top[v])
        {
            add(1, dfn[u] + 1, dfn[v], val);
            v = u;
        }
        else
        {
            add(1, dfn[top[v]], dfn[v], val);
            v = fa[top[v]];
        }
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int a, b, l, t;
        scanf("%d%d%d%d", &a, &b, &l, &t);
        if (t == 1)
        {
            ins(a, b, l);
            ins(b, a, l);
        }
        else
        {
            ++tot;
            q[tot].u = a;
            q[tot].v = b;
            q[tot].dis = l;
        }
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= tot; ++i)
    {
        int w = lca(q[i].u, q[i].v);
        change(w, q[i].v, dis[q[i].u] + dis[q[i].v] + q[i].dis);
        change(w, q[i].u, dis[q[i].u] + dis[q[i].v] + q[i].dis);
    }
    for (int i = 2; i <= n; ++i)
    {
        int num = query(1, dfn[i]);
        if (num == inf)
            printf("-1 ");
        else
            printf("%d ", num - dis[i]);
    }
    return 0;
}