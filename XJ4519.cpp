#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n, m, sum, rt, maxn, minx;
int head[100005], x[100005], y[100005];
int siz[100005], sz[100005], f[100005];
int fa[100005], dep[100005], cnt[100005];
int vis[100005], use[100005], tot[100005];
ll ans;
vector<int> vec[2][100005];
struct node
{
    int v;
    int nxt;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void getrt(int k, int fa)
{
    return;
    f[k] = 0;
    siz[k] = 1;
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
    if (f[k] <= f[rt])
        rt = k;
    return;
}
void dfs1(int k, int fa)
{
    int siz = vec[1][k].size();
    for (int i = 0; i < siz; ++i)
        use[vec[1][k][i]] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
            dfs1(a[d].v, k);
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    minx = max(minx, dep[k]);
    maxn = max(maxn, dep[k]);
    int siz = vec[0][k].size(), num = 0;
    for (int i = 0; i < siz; ++i)
        if (!use[vec[0][k][i]])
            ++num;
    cnt[dep[k]] += num;
    tot[dep[k]] += num;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            dep[a[d].v] = dep[k] + 1;
            dfs2(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
void dfs3(int k, int fa)
{
    int siz = vec[1][k].size();
    for (int i = 0; i < siz; ++i)
        use[vec[1][k][i]] = 0;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
            dfs3(a[d].v, k);
        d = a[d].nxt;
    }
    return;
}
void solve(int k)
{
    if (k == n + 1)
        return;
    // vis[k] = 1;
    maxn = 0;
    ans += (ll)vec[0][k].size() * (vec[0][k].size() - 1) / 2;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            dfs1(a[d].v, k);
            minx = 0;
            dep[a[d].v] = 1;
            dfs2(a[d].v, k);
            for (int i = 1; i <= minx; ++i)
            {
                ans -= (ll)tot[i] * (tot[i] - 1) / 2;
                tot[i] = 0;
            }
            dfs3(a[d].v, k);
        }
        d = a[d].nxt;
    }
    for (int i = 1; i <= maxn; ++i)
    {
        ans += (ll)cnt[i] * (cnt[i] - 1) / 2;
        cnt[i] = 0;
    }
    solve(k + 1);
    // d = head[k];
    // while (d)
    // {
    //     if (!vis[a[d].v])
    //     {
    //         rt = 0;
    //         if (siz[a[d].v] < siz[k])
    //             siz[0] = siz[k];
    //         else
    //             siz[0] = sz[k] - siz[k];
    //         f[0] = siz[0];
    //         getrt(a[d].v, 0);
    //         fa[rt] = k;
    //         sz[rt] = siz[0];
    //         solve(rt);
    //     }
    //     d = a[d].nxt;
    // }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, n + i);
        ins(n + i, u);
        ins(v, n + i);
        ins(n + i, v);
    }
    n = 2 * n - 1;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x[i], &y[i]);
        vec[0][x[i]].push_back(i);
        vec[1][y[i]].push_back(i);
    }
    siz[0] = n;
    f[0] = n;
    getrt(1, 0);
    // solve(rt);
    solve(1);
    printf("%lld", ans);
    return 0;
}