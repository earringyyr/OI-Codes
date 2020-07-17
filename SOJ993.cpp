#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum, head[100005], lg[100005], dep[100005], fa[100005][50], w[100005][50];
struct node
{
    int v;
    int w;
    int next;
} a[200005];
void ins(int u, int v, int ww)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = ww;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int f)
{
    for (int i = 1; i <= lg[dep[k]]; ++i)
    {
        fa[k][i] = fa[fa[k][i - 1]][i - 1];
        w[k][i] = w[k][i - 1] + w[fa[k][i - 1]][i - 1];
    }
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dep[a[d].v] = dep[k] + 1;
            w[a[d].v][0] = a[d].w;
            fa[a[d].v][0] = k;
            dfs(a[d].v, k);
        }
        d = a[d].next;
    }
}
int find(int u, int v)
{
    int ans = 0;
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = lg[dep[u] - dep[v]]; i >= 0; --i)
        if (dep[u] - dep[v] >= (1 << i))
        {
            ans += w[u][i];
            u = fa[u][i];
        }
    if (u == v)
        return ans;
    for (int i = lg[dep[u]]; i >= 0; --i)
        if (dep[u] >= (1 << i) && fa[u][i] != fa[v][i])
        {
            ans += w[u][i];
            ans += w[v][i];
            u = fa[u][i];
            v = fa[v][i];
        }
    ans += w[u][0];
    ans += w[v][0];
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        ins(x, y, z);
        ins(y, x, z);
    }
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    dep[1] = 1;
    dfs(1, 0);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", find(x, y));
    }
    return 0;
}