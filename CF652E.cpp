#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, s, t, col, cnt, num, sum = 1;
int dfn[300005], low[300005], vis[300005];
int head[300005], co[300005], w[300005];
int x[300005], y[300005], z[300005];
int fa[300005], dep[300005], ww[300005];
struct node
{
    int v;
    int w;
    int next;
} a[600005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k, int fa)
{
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            if (!dfn[a[d].v])
            {
                tarjan(a[d].v, k);
                low[k] = min(low[k], low[a[d].v]);
                if (low[a[d].v] > dfn[k])
                    vis[d >> 1] = 1;
            }
            else
                low[k] = min(low[k], dfn[a[d].v]);
        }
        d = a[d].next;
    }
    return;
}
void ddfs(int k)
{
    co[k] = col;
    int d = head[k];
    while (d)
    {
        if (!vis[d >> 1] && !co[a[d].v])
            ddfs(a[d].v);
        d = a[d].next;
    }
    return;
}
void dfs(int k, int ff)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != ff)
        {
            if (a[d].w)
                w[a[d].v] = 1;
            fa[a[d].v] = k;
            dep[a[d].v] = dep[k] + 1;
            dfs(a[d].v, k);
        }
        d = a[d].next;
    }
    return;
}
void find()
{
    if (dep[s] < dep[t])
        swap(s, t);
    while (dep[s] > dep[t])
    {
        num += w[s] + ww[s];
        s = fa[s];
    }
    while (s != t)
    {
        num += w[s] + ww[s] + w[t] + ww[t];
        s = fa[s];
        t = fa[t];
    }
    num += ww[s];
    if (num)
        printf("YES");
    else
        printf("NO");
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
        ins(x[i], y[i], z[i]);
        ins(y[i], x[i], z[i]);
    }
    scanf("%d%d", &s, &t);
    tarjan(1, 0);
    for (int i = 1; i <= n; ++i)
        if (!co[i])
        {
            ++col;
            ddfs(i);
        }
    sum = 1;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= m; ++i)
        if (co[x[i]] == co[y[i]])
        {
            if (z[i])
                ww[co[x[i]]] = 1;
        }
        else
        {
            ins(co[x[i]], co[y[i]], z[i]);
            ins(co[y[i]], co[x[i]], z[i]);
        }
    s = co[s];
    t = co[t];
    dfs(1, 0);
    find();
    return 0;
}