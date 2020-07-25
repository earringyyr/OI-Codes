#include <iostream>
#include <cstdio>
using namespace std;
int n, sum, q[500005], head[500005];
double ans, f[500005], g[500005];
struct node
{
    int v;
    int nxt;
    int p;
} a[1000005];
void ins(int u, int v, int p)
{
    ++sum;
    a[sum].v = v;
    a[sum].p = p;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int fa)
{
    f[k] = 1 - (double)q[k] / 100;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            f[k] = f[k] * (1 - (double)a[d].p / 100 + (double)a[d].p / 100 * f[a[d].v]);
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            g[a[d].v] = f[a[d].v] * (1 - (double)a[d].p / 100 + (double)a[d].p / 100 * g[k] / (1 - (double)a[d].p / 100 + (double)a[d].p / 100 * f[a[d].v]));
            dfs2(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, p;
        scanf("%d%d%d", &u, &v, &p);
        ins(u, v, p);
        ins(v, u, p);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &q[i]);
    dfs1(1, 0);
    g[1] = f[1];
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i)
        ans += 1 - g[i];
    printf("%.6lf", ans);
    return 0;
}