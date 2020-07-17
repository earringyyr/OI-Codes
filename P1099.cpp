#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, ss, s, t, sum, ans, head[305], dis[305], fa[305], vis[305];
struct node
{
    int v;
    int w;
    int next;
} a[605];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int f)
{
    if (dis[k] > dis[t])
        t = k;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v] && a[d].v != f)
        {
            fa[a[d].v] = k;
            dis[a[d].v] = dis[k] + a[d].w;
            dfs(a[d].v, k);
        }
        d = a[d].next;
    }
    return;
}
int main()
{
    ans = 0x7fffffff;
    scanf("%d%d", &n, &ss);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    dfs(1, 0);
    s = t;
    t = 0;
    dis[s] = 0;
    fa[s] = 0;
    memset(fa, 0, sizeof(fa));
    dfs(s, 0);
    int i = t, j = t;
    while (i)
    {
        vis[i] = 1;
        while (fa[j] && dis[i] - dis[fa[j]] <= ss)
            j = fa[j];
        ans = min(ans, max(dis[j], dis[t] - dis[i]));
        i = fa[i];
    }
    i = t;
    while (i)
    {
        dis[i] = 0;
        dfs(i, 0);
        i = fa[i];
    }
    for (i = 1; i <= n; ++i)
        ans = max(ans, dis[i]);
    printf("%d", ans);
    return 0;
}