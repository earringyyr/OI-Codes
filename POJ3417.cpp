#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int sum, n, m, lg[20], head[100005], dep[100005], f[100005][20], val[100005];
struct node
{
    int v;
    int w;
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
void dfs(int k, int fa)
{
    dep[k] = dep[fa] + 1;
    f[k][0] = fa;
    for (int i = 1; lg[i] <= dep[k]; i++)
        f[k][i] = f[f[k][i - 1]][i - 1];
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
            dfs(a[d].v, k);
        d = a[d].next;
    }
}
void ddfs(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            ddfs(a[d].v, k);
            val[k] += val[a[d].v];
        }
        d = a[d].next;
    }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[x] - dep[y] >= lg[i])
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (dep[x] >= (1 << i) && f[x][i] != f[y][i])
        {
            x = f[x][i];
            y = f[y][i];
        }
    return f[x][0];
}
int main()
{
    lg[0] = 1;
    for (int i = 1; i <= 20; i++)
        lg[i] = lg[i - 1] * 2;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        int gu = lca(u, v);
        val[u]++;
        val[v]++;
        val[gu] -= 2;
    }
    ddfs(1, 0);
    int ans = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!val[i])
            ans += m;
        if (val[i] == 1)
            ans += 1;
    }
    printf("%d\n", ans);
    return 0;
}