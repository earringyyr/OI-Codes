#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
int n, m, s, t, sum = 1, ans;
int head[305], cur[305], in[305], out[305], dis[305], l[305], vis[305];
struct node
{
    int v;
    int w;
    int f;
    int nxt;
} a[15005];
void ins(int u, int v, int w, int f)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].f = f;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].f = -f;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
bool spfa()
{
    for (int i = s; i <= t; ++i)
    {
        cur[i] = head[i];
        dis[i] = inf;
        vis[i] = 0;
    }
    int hh = -1, tt = 0;
    l[tt] = s;
    dis[s] = 0;
    vis[s] = 1;
    while (hh < tt)
    {
        ++hh;
        int k = l[hh % t];
        vis[k] = 0;
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && dis[k] + a[d].f < dis[a[d].v])
            {
                dis[a[d].v] = dis[k] + a[d].f;
                if (!vis[a[d].v])
                {
                    l[(++tt) % t] = a[d].v;
                    vis[a[d].v] = 1;
                }
            }
            d = a[d].nxt;
        }
    }
    return dis[t] != inf;
}
int dinic(int k, int flow)
{
    if (k == t)
        return flow;
    vis[k] = 1;
    int d = cur[k], delta, res = 0;
    while (d)
    {
        if (!vis[a[d].v] && a[d].w > 0 && dis[a[d].v] == dis[k] + a[d].f)
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
    if (res == flow)
        vis[k] = 0;
    return res;
}
int main()
{
    scanf("%d", &n);
    s = 1;
    t = n + 1;
    for (int i = 1; i <= n; ++i)
    {
        int k;
        scanf("%d", &k);
        ins(i, t, inf, 0);
        for (int j = 1; j <= k; ++j)
        {
            int b, T;
            scanf("%d%d", &b, &T);
            ins(i, b, inf, T);
            ++out[i];
            ++in[b];
            ans += T;
        }
    }
    s = 0;
    t = n + 2;
    for (int i = 1; i <= n; ++i)
        if (in[i] > out[i])
            ins(s, i, in[i] - out[i], 0);
        else if (in[i] < out[i])
            ins(i, t, out[i] - in[i], 0);
    ins(n + 1, 1, inf, 0);
    while (spfa())
        ans += dis[t] * dinic(s, inf);
    printf("%d", ans);
    return 0;
}