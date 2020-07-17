#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
int t, n, m, sum, head[40005], vis[40005], fa[40005], dep[40005], ans[205], x[205], y[205];
vector<int> c[40005];
struct node
{
    int v;
    int w;
    int next;
} a[80005];
struct point
{
    int id;
    int next;
} b[80005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k, int f)
{
    for (int i = 0; i < c[k].size(); ++i)
        if (vis[c[k][i]])
            ans[c[k][i]] = dep[x[c[k][i]]] + dep[y[c[k][i]]] - 2 * min(dep[getfather(x[c[k][i]])], dep[getfather(y[c[k][i]])]);
        else
            vis[c[k][i]] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dep[a[d].v] = dep[k] + a[d].w;
            tarjan(a[d].v, k);
        }
        d = a[d].next;
    }
    fa[k] = f;
    return;
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d%d", &n, &m);
        sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            fa[i] = i;
            head[i] = 0;
            c[i].clear();
        }
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i < n; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ins(u, v, w);
            ins(v, u, w);
        }
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d", &x[i], &y[i]);
            c[x[i]].push_back(i);
            c[y[i]].push_back(i);
        }
        tarjan(1, 1);
        for (int i = 1; i <= m; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}