#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n, m, sum, rt;
int head[20005], siz[20005], sz[20005];
int f[20005], vis[20005], col[20005];
ll g[20005], ans[200005], s[20005][60];
struct edge
{
    int v;
    int nxt;
} a[40005];
struct node
{
    int id;
    int v;
    int vis;
    node(int aa = 0, int bb = 0, int cc = 0)
    {
        id = aa;
        v = bb;
        vis = cc;
    }
};
vector<node> q[20005];
inline void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void getrt(int k, int fa)
{
    siz[k] = 1;
    f[k] = 0;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            getrt(a[d].v, k);
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
void insert(ll *S, ll x)
{
    if (!x)
        return;
    for (int i = 59; i >= 0; --i)
        if (x & (1LL << i))
        {
            if (!S[i])
            {
                S[i] = x;
                break;
            }
            x ^= S[i];
        }
    return;
}
void merge(ll *G, ll *f1, ll *f2)
{
    for (int i = 59; i >= 0; --i)
        G[i] = f1[i];
    for (int i = 59; i >= 0; --i)
        insert(G, f2[i]);
    return;
}
void dfs1(int k, int fa, int top)
{
    col[k] = top;
    for (int i = 0; i < 60; ++i)
        s[k][i] = s[fa][i];
    insert(s[k], g[k]);
    for (int i = 0; i < q[k].size(); ++i)
        if (!q[k][i].vis && col[q[k][i].v] && col[q[k][i].v] != col[k])
        {
            q[k][i].vis = 1;
            ll g[60];
            merge(g, s[k], s[q[k][i].v]);
            for (int j = 59; j >= 0; --j)
                if ((ans[q[k][i].id] ^ g[j]) > ans[q[k][i].id])
                    ans[q[k][i].id] ^= g[j];
        }
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
            dfs1(a[d].v, k, top);
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    col[k] = 0;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
            dfs2(a[d].v, k);
        d = a[d].nxt;
    }
}
void solve(int k)
{
    vis[k] = 1;
    memset(s[k], 0, sizeof(s[k]));
    for (int i = 59; i >= 0; --i)
        if (g[k] & (1LL << i))
        {
            s[k][i] = g[k];
            break;
        }
    col[k] = n + 1;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
            dfs1(a[d].v, k, a[d].v);
        d = a[d].nxt;
    }
    d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
            dfs2(a[d].v, k);
        d = a[d].nxt;
    }
    d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            rt = 0;
            if (siz[a[d].v] < siz[k])
                siz[0] = siz[a[d].v];
            else
                siz[0] = sz[k] - siz[k];
            f[0] = siz[0];
            getrt(a[d].v, 0);
            sz[rt] = siz[0];
            solve(rt);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &g[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (u == v)
            ans[i] = g[u];
        else
        {
            q[u].push_back(node(i, v, 0));
            q[v].push_back(node(i, u, 0));
        }
    }
    rt = 0;
    siz[0] = n;
    f[0] = n;
    getrt(1, 0);
    sz[rt] = n;
    solve(rt);
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}