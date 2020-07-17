
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, tot, fa[2000005], rev[2000005], ans[2000005], vis[2000005];
struct node
{
    int id;
    int v;
    int next;
} a[2][2000005];
void ins(int id, int u, int v, int pan)
{
    node *b;
    if (pan == 0)
        b = a[0];
    else
        b = a[1];
    if (b[u].id && b[u].v == v)
    {
        fa[b[u].id] = 0;
        fa[id] = 0;
        ans[id] = 1;
        ans[b[u].id] = b[v].next;
        b[u].id = 0;
        b[v].id = 0;
        return;
    }
    bool p = true;
    if (b[u].id)
    {
        p = false;
        fa[b[u].id] = tot;
        rev[b[u].id] = b[u].next;
        b[u].id = 0;
        u = b[u].v;
    }
    if (b[v].id)
    {
        p = false;
        fa[b[v].id] = tot;
        rev[b[v].id] = b[v].next ^ 1;
        b[v].id = 0;
        v = b[v].v;
    }
    b[u].v = v;
    b[v].v = u;
    b[u].next = 1;
    b[v].next = 0;
    if (p)
    {
        b[u].id = id;
        b[v].id = id;
    }
    else
    {
        fa[id] = tot;
        b[u].id = tot;
        b[v].id = tot;
        ++tot;
    }
    return;
}
void dfs(int k)
{
    int x = k, t = 0;
    vis[x] = 1;
    while (a[t][x].id)
    {
        ans[a[t][x].id] = a[t][x].next;
        if (vis[a[t][x].v])
            return;
        vis[a[t][x].v] = 1;
        x = a[t][x].v;
        t ^= 1;
    }
    x = k;
    t = 1;
    while (a[t][x].id)
    {
        ans[a[t][x].id] = a[t][x].next ^ 1;
        if (vis[a[t][x].v])
            return;
        vis[a[t][x].v] = 1;
        x = a[t][x].v;
        t ^= 1;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    tot = m + 1;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(i, u, v, w - 1);
    }
    for (int i = 0; i < n; ++i)
        if (!vis[i])
            dfs(i);
    for (int i = tot; i >= 1; --i)
        if (fa[i])
            ans[i] = ans[fa[i]] ^ rev[i];
    for (int i = 1; i <= m; i++)
        printf("%d", ans[i]);
    return 0;
}