#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum, id, ans, head[10005], num[10005], vis[10005];
struct node
{
    int v;
    int nxt;
} a[2000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            ++num[a[d].v];
            if (num[a[d].v] > num[id])
                id = a[d].v;
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    for (int i = 1; i <= n; ++i)
    {
        id = -1;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (id == -1 || num[j] > num[id]))
                id = j;
        vis[id] = 1;
        int d = head[id];
        while (d)
        {
            if (!vis[a[d].v])
                ++num[a[d].v];
            d = a[d].nxt;
        }
    }
    for (int i = 1; i <= n; ++i)
        ans = max(ans, num[i] + 1);
    printf("%d", ans);
    return 0;
}