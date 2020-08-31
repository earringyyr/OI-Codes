#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, Q, sum, rt, cnt, tot;
int head[100005], vis[100005];
int dis[100005], dfn[100005], use[100005];
int siz[100005], sz[100005], f[100005], fa[100005];
int f1[100005], f2[100005], g1[100005], g2[100005];
int lg[200005], st[200005][20];
struct node
{
    int v;
    int vv;
    int w;
    int nxt;
} a[200005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa)
{
    st[++cnt][0] = dis[k];
    dfn[k] = cnt;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dis[a[d].v] = dis[k] + a[d].w;
            dfs(a[d].v, k);
            st[++cnt][0] = dis[k];
        }
        d = a[d].nxt;
    }
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
void getdis(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
            getdis(a[d].v, k);
        d = a[d].nxt;
    }
    return;
}
void solve(int k)
{
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            rt = 0;
            if (siz[a[d].v] < siz[k])
                siz[0] = siz[a[d].v];
            else
                siz[0] = sz[k] - siz[k];
            getrt(a[d].v, 0);
            sz[rt] = siz[0];
            fa[rt] = k;
            a[d].vv = rt;
            solve(rt);
        }
        d = a[d].nxt;
    }
    return;
}
int dist(int u, int v)
{
    int x = dfn[u], y = dfn[v];
    if (x > y)
        swap(x, y);
    int t = lg[y - x + 1];
    return dis[u] + dis[v] - 2 * min(st[x][t], st[y - (1 << t) + 1][t]);
}
int calc(int k)
{
    int d = k, ans = 0;
    while (d)
    {
        ans += f2[d] + f1[d] * dist(k, d);
        d = fa[d];
    }
    d = k;
    while (fa[d])
    {
        ans -= g2[d] + g1[d] * dist(k, fa[d]);
        d = fa[d];
    }
    return ans;
}
int query(int k)
{
    use[k] = 1;
    int ans = calc(k);
    int d = head[k];
    while (d)
    {
        if (!use[a[d].v])
        {
            int tmp = calc(a[d].v);
            if (tmp < ans)
            {
                ans = query(a[d].vv);
                break;
            }
        }
        d = a[d].nxt;
    }
    use[k] = 0;
    return ans;
}
signed main()
{
    scanf("%lld%lld", &n, &Q);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    dfs(1, 0);
    for (int i = 2; i <= cnt; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = cnt; i >= 1; --i)
        for (int j = 1; j <= lg[cnt - i + 1]; ++j)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    siz[0] = n;
    f[0] = n;
    getrt(1, 0);
    sz[rt] = n;
    solve(rt);
    for (int i = 1; i <= n; ++i)
        if (!fa[i])
        {
            rt = i;
            break;
        }
    for (int i = 1; i <= Q; ++i)
    {
        int u, e;
        scanf("%lld%lld", &u, &e);
        int d = u;
        while (d)
        {
            f1[d] += e;
            f2[d] += dist(u, d) * e;
            d = fa[d];
        }
        d = u;
        while (fa[d])
        {
            g1[d] += e;
            g2[d] += dist(u, fa[d]) * e;
            d = fa[d];
        }
        tot += e;
        printf("%lld\n", query(rt));
    }
    return 0;
}