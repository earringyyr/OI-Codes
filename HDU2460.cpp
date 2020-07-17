#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int t, n, m, q, sum, cnt, col;
int f[100005], vis[100005];
int dfn[100005], low[100005], head[100005];
struct node
{
    int v;
    int next;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k, int fa)
{
    f[k] = fa;
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    int d = head[k];
    while (d)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v, k);
            low[k] = min(low[k], low[a[d].v]);
            if (low[a[d].v] > dfn[k])
            {
                vis[a[d].v] = 1;
                ++col;
            }
        }
        else if (a[d].v != fa)
            low[k] = min(low[k], dfn[a[d].v]);
        d = a[d].next;
    }
}
void lca(int u, int v)
{
    if (dfn[u] > dfn[v])
        swap(u, v);
    while (dfn[v] > dfn[u])
    {
        if (vis[v])
            --col;
        vis[v] = 0;
        v = f[v];
    }
    while (u != v)
    {
        if (vis[u])
            --col;
        if (vis[v])
            --col;
        vis[u] = 0;
        vis[v] = 0;
        u = f[u];
        v = f[v];
    }
    return;
}
int main()
{
    while (scanf("%d%d", &n, &m) == 2)
    {
        if (n == 0 && m == 0)
            break;
        ++t;
        sum = 1;
        cnt = 0;
        col = 0;
        memset(head, 0, sizeof(head));
        memset(vis, 0, sizeof(vis));
        memset(dfn, 0, sizeof(dfn));
        printf("Case %d:\n", t);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            ins(u, v);
            ins(v, u);
        }
        tarjan(1, 0);
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            lca(u, v);
            printf("%d\n", col);
        }
        putchar('\n');
    }
    return 0;
}