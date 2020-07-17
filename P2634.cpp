#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, sum, rt, ans;
int head[20005];
int siz[20005], f[20005], vis[20005];
int num[20005], dis[20005];
struct node
{
    int u;
    int v;
    int w;
    int nxt;
} a[40005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int fa)
{
    siz[k] = 1;
    f[k] = 0;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            f[k] = max(f[k], siz[a[d].v]);
        }
        d = a[d].nxt;
    }
    f[k] = max(f[k], siz[0] - siz[k]);
    if (f[k] < f[rt])
        rt = k;
    return;
}
void dfs2(int k, int fa)
{
    ++num[dis[k]];
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            dis[a[d].v] = (dis[k] + a[d].w) % 3;
            dfs2(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
int calc(int k, int val)
{
    memset(num, 0, sizeof(num));
    dis[k] = val % 3;
    dfs2(k, 0);
    return num[0] * num[0] + 2 * num[1] * num[2];
}
void solve(int k)
{
    ans += calc(k, 0);
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            ans -= calc(a[d].v, a[d].w);
            rt = 0;
            siz[0] = siz[a[d].v];
            f[0] = siz[a[d].v];
            dfs1(a[d].v, 0);
            solve(rt);
        }
        d = a[d].nxt;
    }
    return;
}
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        ins(x, y, w);
        ins(y, x, w);
    }
    siz[0] = n;
    f[0] = n;
    dfs1(1, 0);
    solve(rt);
    int g = gcd(ans, n * n);
    printf("%d/%d", ans / g, n * n / g);
    return 0;
}