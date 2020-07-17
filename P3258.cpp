#include <iostream>
#include <cstdio>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, sum, cnt;
int a[300005], head[300005];
int dfn[300005], top[300005];
int siz[300005], dep[300005];
int fa[300005], son[300005];
struct node
{
    int u;
    int v;
    int next;
} s[600005];
struct tree
{
    int l;
    int r;
    int num;
    int lazy;
} tr[1200005];
inline void ins(int u, int v)
{
    ++sum;
    s[sum].u = u;
    s[sum].v = v;
    s[sum].next = head[u];
    head[u] = sum;
    return;
}
inline void dfs1(int id, int f, int deep)
{
    siz[id] = 1;
    son[id] = -1;
    dep[id] = deep;
    fa[id] = f;
    int d = head[id];
    while (d)
    {
        if (s[d].v != fa[id])
        {
            dfs1(s[d].v, id, deep + 1);
            siz[id] += siz[s[d].v];
            if (son[id] == -1 || siz[s[d].v] > siz[son[id]])
                son[id] = s[d].v;
        }
        d = s[d].next;
    }
    return;
}
inline void dfs2(int id, int topf)
{
    top[id] = topf;
    dfn[id] = ++cnt;
    if (son[id] != -1)
        dfs2(son[id], topf);
    int d = head[id];
    while (d)
    {
        if (s[d].v != son[id] && s[d].v != fa[id])
            dfs2(s[d].v, s[d].v);
        d = s[d].next;
    }
    return;
}
inline void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
        return;
    int mid = (tr[id].l + tr[id].r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
inline void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        tr[lch].lazy += tr[id].lazy;
        tr[rch].lazy += tr[id].lazy;
        tr[lch].num += tr[id].lazy * (tr[lch].r - tr[lch].l + 1);
        tr[rch].num += tr[id].lazy * (tr[rch].r - tr[rch].r + 1);
        tr[id].lazy = 0;
    }
    return;
}
inline void add(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].lazy += val;
        tr[id].num += (tr[id].r - tr[id].l + 1) * val;
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
inline int ask(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return ask(lch, l, mid) + ask(rch, mid + 1, r);
}
inline void ask_lian(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        add(1, dfn[top[u]], dfn[u], 1);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    add(1, dfn[u], dfn[v], 1);
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ins(x, y);
        ins(y, x);
    }
    dfs1(1, 0, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i < n; ++i)
    {
        ask_lian(a[i], a[i + 1]);
        add(1, dfn[a[i + 1]], dfn[a[i + 1]], -1);
    }
    for (int i = 1; i <= n; ++i)
        cout << ask(1, dfn[i], dfn[i]) << endl;
    return 0;
}