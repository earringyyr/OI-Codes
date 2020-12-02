#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sum, tot, cnt;
int t[100005], head[100005], rt[100005];
int fa[100005], dep[100005], siz[100005];
int son[100005], top[100005], dfn[100005];
struct node
{
    int v;
    int nxt;
} a[200005];
struct tree
{
    int l;
    int r;
    int num;
} tr[2500005];
void add(int y, int &x, int l, int r, int w)
{
    x = ++cnt;
    tr[x] = tr[y];
    if (l == r)
    {
        ++tr[x].num;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[y].l, tr[x].l, l, mid, w);
    else
        add(tr[y].r, tr[x].r, mid + 1, r, w);
    return;
}
int ask(int x, int y, int l, int r, int w)
{
    if (l == r)
        return tr[y].num - tr[x].num;
    int mid = (l + r) >> 1;
    if (w <= mid)
        return ask(tr[x].l, tr[y].l, l, mid, w);
    else
        return ask(tr[x].r, tr[y].r, mid + 1, r, w);
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int f)
{
    fa[k] = f;
    siz[k] = 1;
    son[k] = -1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dep[a[d].v] = dep[k] + 1;
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
}
void dfs2(int k, int topf)
{
    top[k] = topf;
    dfn[k] = ++tot;
    if (topf == k)
        add(rt[k], rt[k], 1, n, t[k]);
    else
        add(rt[fa[k]], rt[k], 1, n, t[k]);
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
int query(int u, int v, int w)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        if (ask(rt[top[u]], rt[u], 1, n, w) > 0)
            return true;
        if (t[top[u]] == w)
            return true;
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    if (ask(rt[u], rt[v], 1, n, w) > 0)
        return true;
    if (t[u] == w)
        return true;
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &t[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (query(u, v, w))
            putchar('1');
        else
            putchar('0');
    }
    return 0;
}