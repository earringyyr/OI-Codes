#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, m, sum, cnt, len;
int in[50005], out[50005], c[50005];
int head[50005], fa[50005], siz[50005];
int son[50005], top[50005], dep[50005];
int vis[50005], num[50005];
int ans[100005], dfn[100005];
int q[100005][2];
struct edge
{
    int v;
    int nxt;
} a[100005];
struct node
{
    int id;
    int x;
    int y;
    int lca;
} l[100005];
bool cmp(node aa, node bb)
{
    if (aa.x / len == bb.x / len)
        return aa.y < bb.y;
    return aa.x < bb.x;
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
    siz[k] = 1;
    son[k] = -1;
    fa[k] = f;
    in[k] = ++cnt;
    dfn[cnt] = k;
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
    out[k] = ++cnt;
    dfn[cnt] = k;
    return;
}
void dfs2(int k, int topf)
{
    top[k] = topf;
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
int lca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    return u;
}
void add(int x)
{
    if (!num[c[x]])
        ++ans[0];
    ++num[c[x]];
    return;
}
void del(int x)
{
    --num[c[x]];
    if (!num[c[x]])
        --ans[0];
    return;
}
void move(int x)
{
    if (vis[x])
        del(x);
    else
        add(x);
    vis[x] ^= 1;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(0, 0);
    dfs2(0, 0);
    len = sqrt(cnt);
    for (int i = 1; i <= m; ++i)
    {
        l[i].id = i;
        scanf("%d%d%d%d", &l[i].x, &l[i].y, &q[i][0], &q[i][1]);
        if (dep[l[i].x] > dep[l[i].y])
            swap(l[i].x, l[i].y);
        if (l[i].x == lca(l[i].x, l[i].y))
        {
            l[i].x = in[l[i].x];
            l[i].y = in[l[i].y];
        }
        else
        {
            l[i].lca = lca(l[i].x, l[i].y);
            l[i].x = out[l[i].x];
            l[i].y = in[l[i].y];
        }
    }
    sort(l + 1, l + m + 1, cmp);
    int x = 1, y = 0;
    for (int i = 1; i <= m; ++i)
    {
        while (x < l[i].x)
            move(dfn[x++]);
        while (x > l[i].x)
            move(dfn[--x]);
        while (y < l[i].y)
            move(dfn[++y]);
        while (y > l[i].y)
            move(dfn[y--]);
        if (l[i].lca)
            move(l[i].lca);
        ans[l[i].id] = ans[0];
        if (q[l[i].id][0] != q[l[i].id][1] && num[q[l[i].id][0]] && num[q[l[i].id][1]])
            --ans[l[i].id];
        if (l[i].lca)
            move(l[i].lca);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}