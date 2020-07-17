#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, sum, rt, cnt, K[105], num[105], ans[105];
int head[10005], siz[10005], sz[10005], f[10005], vis[10005], dis[10005], q[10005], use[10000005];
struct node
{
    int v;
    int w;
    int nxt;
} a[20005];
inline void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
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
void dfs(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            dis[a[d].v] = dis[k] + a[d].w;
            if (dis[a[d].v] <= 1e7)
            {
                q[++cnt] = a[d].v;
                for (int i = 1; i <= m; ++i)
                    if (dis[a[d].v] <= K[i])
                        num[i] += use[K[i] - dis[a[d].v]];
                ++use[dis[a[d].v]];
                dfs(a[d].v, k);
            }
        }
        d = a[d].nxt;
    }
    return;
}
void calc(int k, int val, int type)
{
    memset(num, 0, sizeof(num));
    cnt = 0;
    dis[k] = val;
    ++use[dis[k]];
    q[++cnt] = k;
    dfs(k, 0);
    for (int i = 1; i <= cnt; ++i)
        --use[dis[q[i]]];
    for (int i = 1; i <= m; ++i)
        ans[i] += num[i] * type;
    return;
}
void solve(int k)
{
    vis[k] = 1;
    calc(k, 0, 1);
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            calc(a[d].v, a[d].w, -1);
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
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    for (int i = 1; i <= m; ++i)
        scanf("%d", &K[i]);
    rt = 0;
    siz[0] = n;
    f[0] = n;
    getrt(1, 0);
    sz[rt] = n;
    solve(rt);
    for (int i = 1; i <= m; ++i)
        if (ans[i])
            puts("AYE");
        else
            puts("NAY");
    return 0;
}