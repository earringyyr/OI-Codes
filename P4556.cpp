#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sum, cnt;
int head[100005], dep[100005], top[100005], ans[100005];
int son[100005], rt[100005], f[100005], siz[100005];
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
    int ans;
} tr[5100005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int fa)
{
    f[k] = fa;
    son[k] = -1;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
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
void dfs2(int k, int fa, int topf)
{
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], k, topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && a[d].v != son[k])
            dfs2(a[d].v, k, a[d].v);
        d = a[d].nxt;
    }
    return;
}
int lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = f[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}
void pushup(int x)
{
    if (tr[tr[x].l].num >= tr[tr[x].r].num)
    {
        tr[x].num = tr[tr[x].l].num;
        tr[x].ans = tr[tr[x].l].ans;
    }
    else
    {
        tr[x].num = tr[tr[x].r].num;
        tr[x].ans = tr[tr[x].r].ans;
    }
    if (!tr[x].num)
        tr[x].ans = 0;
    return;
}
void add(int &x, int l, int r, int w, int val)
{
    if (!x)
        x = ++cnt;
    if (l == r)
    {
        tr[x].num += val;
        tr[x].ans = l;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[x].l, l, mid, w, val);
    else
        add(tr[x].r, mid + 1, r, w, val);
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
void dfs(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k);
            rt[k] = merge(rt[k], rt[a[d].v], 1, 100000);
        }
        d = a[d].nxt;
    }
    ans[k] = tr[rt[k]].ans;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0, 1);
    tr[0].num = -0x7fffffff;
    for (int i = 1; i <= m; ++i)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int w = lca(x, y);
        if (w == x || w == y)
        {
            if (w == y)
                swap(x, y);
            add(rt[y], 1, 100000, z, 1);
            add(rt[f[x]], 1, 100000, z, -1);
        }
        else
        {
            add(rt[x], 1, 100000, z, 1);
            add(rt[y], 1, 100000, z, 1);
            add(rt[w], 1, 100000, z, -1);
            add(rt[f[w]], 1, 100000, z, -1);
        }
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}