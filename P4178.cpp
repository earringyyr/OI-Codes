#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, K, rt, sum, num, ans;
int head[40005], vis[40005], dis[40005];
int siz[40005], sz[40005], f[40005];
int c[20005], q[40005];
struct node
{
    int v;
    int w;
    int nxt;
} a[80005];
void ins(int u, int v, int w)
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
    if (dis[k] > K)
        return;
    q[++num] = k;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa && !vis[a[d].v])
        {
            dis[a[d].v] = dis[k] + a[d].w;
            dfs(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
bool cmp(int aa, int bb)
{
    return dis[aa] < dis[bb];
}
int calc(int k, int val)
{
    int cnt = 0;
    num = 0;
    dis[k] = val;
    dfs(k, 0);
    sort(q + 1, q + num + 1, cmp);
    int j = num;
    for (int i = 1; i <= num && i <= j; ++i)
    {
        while (i <= j && dis[q[i]] + dis[q[j]] > K)
            --j;
        if (i <= j)
            cnt += j - i;
    }
    return cnt;
}
void solve(int k)
{
    vis[k] = 1;
    ans += calc(k, 0);
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            rt = 0;
            if (siz[k] > siz[a[d].v])
                siz[0] = siz[a[d].v];
            else
                siz[0] = sz[k] - siz[k];
            f[0] = siz[0];
            getrt(a[d].v, 0);
            sz[rt] = siz[0];
            ans -= calc(a[d].v, a[d].w);
            solve(rt);
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
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    scanf("%d", &K);
    rt = 0;
    f[0] = n;
    siz[0] = n;
    getrt(1, 0);
    sz[rt] = n;
    solve(rt);
    printf("%d", ans);
    return 0;
}