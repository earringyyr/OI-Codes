#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum;
int head[50005], lg[50005], dep[50005];
int f[50005][50], dp[50005][50];
struct node
{
    int v;
    int w;
    int next;
} a[100005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa, int w)
{
    dep[k] = dep[fa] + 1;
    f[k][0] = fa;
    dp[k][0] = w;
    for (int i = 1; i <= lg[dep[k]]; ++i)
    {
        f[k][i] = f[f[k][i - 1]][i - 1];
        dp[k][i] = dp[k][i - 1] + dp[f[k][i - 1]][i - 1];
    }
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
            dfs(a[d].v, k, a[d].w);
        d = a[d].next;
    }
    return;
}
int lca(int u, int v)
{
    int ans = 0;
    while (dep[u] > dep[v])
    {
        ans += dp[u][lg[dep[u] - dep[v]]];
        u = f[u][lg[dep[u] - dep[v]]];
    }
    while (dep[u] < dep[v])
    {
        ans += dp[v][lg[dep[v] - dep[u]]];
        v = f[v][lg[dep[v] - dep[u]]];
    }
    if (u == v)
        return ans;
    for (int i = lg[dep[u]]; i >= 0; --i)
        if (f[u][i] != f[v][i])
        {
            ans += dp[u][i];
            ans += dp[v][i];
            u = f[u][i];
            v = f[v][i];
        }
    ans += dp[u][0];
    ans += dp[v][0];
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + ((1 << (lg[i - 1] + 1)) == i ? 1 : 0);
    for (int i = 1; i < n; ++i)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        ins(u, v, c);
        ins(v, u, c);
    }
    dep[0] = -1;
    dfs(0, 0, 0);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", lca(u, v));
    }
    return 0;
}