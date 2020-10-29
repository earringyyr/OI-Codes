#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
#define inf 0x7fffffffffffffff
using namespace std;
int n, m, s, t, ans, sum = 1;
int head[10005], lev[100005], cur[100005];
struct node
{
    int v;
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
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
bool bfs()
{
    int hh = 0, tt = 1, q[100005];
    memset(lev, -1, sizeof(lev));
    for (int i = 1; i <= n; ++i)
        cur[i] = head[i];
    q[1] = s;
    lev[s] = 0;
    while (hh < tt)
    {
        ++hh;
        int k = q[hh];
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && lev[a[d].v] == -1)
            {
                lev[a[d].v] = lev[k] + 1;
                q[++tt] = a[d].v;
                if (a[d].v == t)
                    return true;
            }
            d = a[d].nxt;
        }
    }
    return false;
}
int dinic(int k, int flow)
{
    if (k == t)
        return flow;
    int d = cur[k], res = 0, delta;
    while (d)
    {
        if (a[d].w > 0 && lev[k] + 1 == lev[a[d].v])
        {
            delta = dinic(a[d].v, min(a[d].w, flow - res));
            if (delta)
            {
                a[d].w -= delta;
                a[d ^ 1].w += delta;
                res += delta;
                if (res == flow)
                    break;
            }
        }
        d = a[d].nxt;
        cur[k] = d;
    }
    if (res != flow)
        lev[k] = -1;
    return res;
}
signed main()
{
    scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        ins(u, v, w);
    }
    while (bfs())
        ans += dinic(s, inf);
    printf("%lld", ans);
    return 0;
}