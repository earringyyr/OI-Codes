#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, m, sum, cnt, q;
int siz[10005], vis[10005];
int head[10005], c[10005], fafa[10005];
int fa[10005], dep[10005], son[10005];
int top[10005], dfn[10005], num[10005];
struct node
{
    int u;
    int v;
    int w;
    int next;
} a[100005], b[50005];
struct tree
{
    int l;
    int r;
    int mi;
} tr[40005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].u = u;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool cmp(node x, node y)
{
    return x.w > y.w;
}
int getfather(int x)
{
    if (fafa[x] == x)
        return x;
    fafa[x] = getfather(fafa[x]);
    return fafa[x];
}
void kruskal()
{
    sort(b + 1, b + m + 1, cmp);
    for (int i = 1; i <= n; ++i)
        fafa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        if (getfather(b[i].u) != getfather(b[i].v))
        {
            fafa[getfather(b[i].u)] = getfather(b[i].v);
            ins(b[i].u, b[i].v, b[i].w);
            ins(b[i].v, b[i].u, b[i].w);
        }
    }
    return;
}
void dfs1(int id, int f, int deep)
{
    vis[id] = 1;
    siz[id] = 1;
    fa[id] = f;
    dep[id] = deep;
    son[id] = -1;
    int d = head[id];
    while (d)
    {
        if (a[d].v != f)
        {
            c[a[d].v] = a[d].w;
            dfs1(a[d].v, id, deep + 1);
            siz[id] += siz[a[d].v];
            if (son[id] == -1 || siz[a[d].v] > siz[son[id]])
                son[id] = a[d].v;
        }
        d = a[d].next;
    }
    return;
}
void dfs2(int id, int topf)
{
    top[id] = topf;
    dfn[id] = ++sum;
    num[sum] = id;
    if (son[id] != -1)
        dfs2(son[id], topf);
    int d = head[id];
    while (d)
    {
        if (a[d].v != fa[id] && a[d].v != son[id])
            dfs2(a[d].v, a[d].v);
        d = a[d].next;
    }
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].mi = c[num[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].mi = min(tr[lch].mi, tr[rch].mi);
    return;
}
int ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].mi;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return min(ask(lch, l, mid), ask(rch, mid + 1, r));
}
int ask_lian(int x, int y)
{
    int ans = 1000000;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans = min(ans, ask(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y])
        swap(x, y);
    if (dfn[x] + 1 <= dfn[y])
        ans = min(ans, ask(1, dfn[x] + 1, dfn[y]));
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &b[i].u, &b[i].v, &b[i].w);
    kruskal();
    sum = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            c[i] = 1000000;
            dfs1(i, 0, 1);
            dfs2(i, i);
        }
    build(1, 1, n);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (getfather(x) == getfather(y))
            printf("%d\n", ask_lian(x, y));
        else
            printf("-1\n");
    }
    return 0;
}