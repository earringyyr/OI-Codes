#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, K, sum, rt, cnt, ans;
int head[10005], vis[10005], siz[10005];
int sz[10005], f[10005], dis[10005];
int c[10000005], q[10005];
struct node
{
    int v;
    int w;
    int nxt;
} a[20005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= 1000 * n)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
void getrt(int k, int fa)
{
    f[k] = 0;
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v] && a[d].v != fa)
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
int dfs(int k, int fa)
{
    int num = 0;
    q[++cnt] = k;
    add(dis[k] + 1, 1);
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v] && a[d].v != fa)
        {
            dis[a[d].v] = dis[k] + a[d].w;
            if (dis[a[d].v] <= K)
            {
                num += ask(K - dis[a[d].v] + 1);
                num += dfs(a[d].v, k);
            }
        }
        d = a[d].nxt;
    }
    return num;
}
void calc(int k, int val, int type)
{
    cnt = 0;
    dis[k] = val;
    int num = dfs(k, 0);
    for (int i = 1; i <= cnt; ++i)
        add(dis[q[i]] + 1, -1);
    ans += type * num;
    return;
}
void solve(int k)
{
    calc(k, 0, 1);
    vis[k] = 1;
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
    while (scanf("%d%d", &n, &K))
    {
        if (!n && !K)
            break;
        rt = 0;
        ans = 0;
        sum = 0;
        memset(head, 0, sizeof(head));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i < n; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ins(u, v, w);
            ins(v, u, w);
        }
        f[0] = n;
        siz[0] = n;
        getrt(1, 0);
        sz[rt] = n;
        solve(rt);
        printf("%d\n", ans);
    }
    return 0;
}