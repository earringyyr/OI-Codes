#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int n, m, sum;
int head[300005], w[300005], siz[300005];
int dep[300005], fa[300005], son[300005];
int s[300005], t[300005], k[300005];
int dis[300005], top[300005], ans[300005];
int num[300005], b1[600005], b2[600005];
vector<int> v1[300005], v2[300005];
struct node
{
    int v;
    int nxt;
} a[600005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k)
{
    son[k] = -1;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k])
        {
            fa[a[d].v] = k;
            dep[a[d].v] = dep[k] + 1;
            dfs1(a[d].v);
            siz[k] += siz[a[d].v];
            if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
}
void dfs2(int k, int topf)
{
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k] && a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
    return;
}
int lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}
void dfs3(int k)
{
    int p1 = b1[w[k] + dep[k]], p2 = b2[w[k] - dep[k] + n];
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k])
            dfs3(a[d].v);
        d = a[d].nxt;
    }
    b1[dep[k]] += num[k];
    for (int i = 0; i < v1[k].size(); ++i)
        ++b2[dis[v1[k][i]] - dep[t[v1[k][i]]] + n];
    ans[k] += b1[w[k] + dep[k]] - p1 + b2[w[k] - dep[k] + n] - p2;
    for (int i = 0; i < v2[k].size(); ++i)
    {
        --b1[dep[s[v2[k][i]]]];
        --b2[dis[v2[k][i]] - dep[t[v2[k][i]]] + n];
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &s[i], &t[i]);
        k[i] = lca(s[i], t[i]);
        ++num[s[i]];
        v1[t[i]].push_back(i);
        v2[k[i]].push_back(i);
        dis[i] = dep[s[i]] + dep[t[i]] - 2 * dep[k[i]];
        if (dep[k[i]] + w[k[i]] == dep[s[i]])
            --ans[k[i]];
    }
    dfs3(1);
    for (int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    return 0;
}