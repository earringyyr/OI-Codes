#include <iostream>
#include <cstdio>
#define inf 1000000000000
using namespace std;
char s[2];
int n, m, sum;
int fa[100005][20];
int p[100005], head[100005];
int lg[100005], dep[100005];
long long f[100005][2];
long long dp[100005][20][2][2];
struct node
{
    int v;
    int next;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int father, int deep)
{
    dep[k] = deep;
    f[k][1] = p[k];
    fa[k][0] = father;
    for (int i = 1; i <= lg[dep[k]]; ++i)
        fa[k][i] = fa[fa[k][i - 1]][i - 1];
    int d = head[k];
    while (d)
    {
        if (a[d].v != father)
        {
            dfs1(a[d].v, k, deep + 1);
            f[k][0] += f[a[d].v][1];
            f[k][1] += min(f[a[d].v][0], f[a[d].v][1]);
        }
        d = a[d].next;
    }
    return;
}
void dfs2(int k)
{
    dp[k][0][0][0] = inf;
    dp[k][0][1][0] = f[fa[k][0]][0] - f[k][1];
    dp[k][0][0][1] = f[fa[k][0]][1] - min(f[k][0], f[k][1]);
    dp[k][0][1][1] = f[fa[k][0]][1] - min(f[k][0], f[k][1]);
    for (int i = 1; i <= lg[dep[k]]; ++i)
    {
        dp[k][i][0][0] = min(dp[k][i - 1][0][0] + dp[fa[k][i - 1]][i - 1][0][0], dp[k][i - 1][0][1] + dp[fa[k][i - 1]][i - 1][1][0]);
        dp[k][i][0][1] = min(dp[k][i - 1][0][0] + dp[fa[k][i - 1]][i - 1][0][1], dp[k][i - 1][0][1] + dp[fa[k][i - 1]][i - 1][1][1]);
        dp[k][i][1][0] = min(dp[k][i - 1][1][0] + dp[fa[k][i - 1]][i - 1][0][0], dp[k][i - 1][1][1] + dp[fa[k][i - 1]][i - 1][1][0]);
        dp[k][i][1][1] = min(dp[k][i - 1][1][0] + dp[fa[k][i - 1]][i - 1][0][1], dp[k][i - 1][1][1] + dp[fa[k][i - 1]][i - 1][1][1]);
    }
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k][0])
            dfs2(a[d].v);
        d = a[d].next;
    }
    return;
}
long long query(int u, int x, int v, int y)
{
    int w;
    long long ans = inf;
    long long t0, t1, k0, k1;
    long long u0 = inf, u1 = inf;
    long long v0 = inf, v1 = inf;
    long long l0 = inf, l1 = inf;
    if (dep[u] < dep[v])
    {
        swap(u, v);
        swap(x, y);
    }
    if (x)
        u1 = f[u][1];
    else
        u0 = f[u][0];
    if (y)
        v1 = f[v][1];
    else
        v0 = f[v][0];
    for (int i = lg[dep[u] - dep[v]]; i >= 0; --i)
        if (dep[u] - (1 << i) >= dep[v])
        {
            t0 = u0;
            t1 = u1;
            u0 = min(t0 + dp[u][i][0][0], t1 + dp[u][i][1][0]);
            u1 = min(t0 + dp[u][i][0][1], t1 + dp[u][i][1][1]);
            u = fa[u][i];
        }
    if (u == v)
    {
        w = u;
        if (y)
            l1 = u1;
        else
            l0 = u0;
    }
    else
    {
        for (int i = lg[dep[u]]; i >= 0; --i)
            if (fa[u][i] != fa[v][i])
            {
                t0 = u0;
                t1 = u1;
                k0 = v0;
                k1 = v1;
                u0 = min(t0 + dp[u][i][0][0], t1 + dp[u][i][1][0]);
                u1 = min(t0 + dp[u][i][0][1], t1 + dp[u][i][1][1]);
                v0 = min(k0 + dp[v][i][0][0], k1 + dp[v][i][1][0]);
                v1 = min(k0 + dp[v][i][0][1], k1 + dp[v][i][1][1]);
                u = fa[u][i];
                v = fa[v][i];
            }
        w = fa[u][0];
        l0 = f[w][0] - f[u][1] - f[v][1] + u1 + v1;
        l1 = f[w][1] - min(f[u][0], f[u][1]) - min(f[v][0], f[v][1]) + min(u0, u1) + min(v0, v1);
    }
    if (w != 1)
        for (int i = lg[dep[w]]; i >= 0; --i)
            if (dep[w] - (1 << i) >= 1)
            {
                t0 = l0, t1 = l1;
                l0 = min(t0 + dp[w][i][0][0], t1 + dp[w][i][1][0]);
                l1 = min(t0 + dp[w][i][0][1], t1 + dp[w][i][1][1]);
                w = fa[w][i];
            }
    ans = min(l0, l1);
    if (ans >= inf)
        ans = -1;
    return ans;
}
int main()
{
    freopen("defense.in", "r", stdin);
    freopen("defense.out", "w", stdout);
    scanf("%d%d%s", &n, &m, s);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &p[i]);
    lg[0] = -1;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
        lg[i] = lg[i >> 1] + 1;
    }
    lg[n] = lg[n >> 1] + 1;
    dfs1(1, 0, 1);
    dfs2(1);
    for (int i = 1; i <= m; ++i)
    {
        int u, x, v, y;
        scanf("%d%d%d%d", &u, &x, &v, &y);
        printf("%lld\n", query(u, x, v, y));
    }
    return 0;
}