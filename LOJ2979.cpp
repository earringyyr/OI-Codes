#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x7f7f7f7f
using namespace std;
int n, m, s, t, cnt, sum = 1, ans, cost;
int head[], cur[], dis[], use[];
int l[][], r[][];
int rt[];
struct edge
{
    int v;
    int w;
    int f;
    int nxt;
} a[];
struct tree
{
    int l;
    int r;
} tr[][];
int build(int l, int r)
{
    int x = ++cnt;
    if (l == r)
        return x;
    int mid = (l + r) >> 1;
    tr[x].l = build(l, mid);
    tr[x].r = build(mid + 1, r);
    return x;
}
inline void ins(int u, int v, int w, int f)
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
inline bool spfa()
{
    memset(use, 0, sizeof(use));
    memset(dis, 0x7f, sizeof(dis));
    for (int i = s; i <= t; ++i)
        cur[i] = head[i];
    int vis[5005] = {0};
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    dis[s] = 0;
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        vis[k] = 0;
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && dis[a[d].v] > dis[k] + a[d].f)
            {
                dis[a[d].v] = dis[k] + a[d].f;
                if (!vis[a[d].v])
                {
                    q.push(a[d].v);
                    vis[a[d].v] = 1;
                }
            }
            d = a[d].nxt;
        }
    }
    if (dis[t] < inf)
        return true;
    else
        return false;
}
inline int dinic(int k, int flow)
{
    if (k == t)
    {
        cost += dis[t] * flow;
        return flow;
    }
    use[k] = 1;
    int d = cur[k], res = 0, delta;
    while (d)
    {
        if (!use[a[d].v] && a[d].w > 0 && dis[k] + a[d].f == dis[a[d].v])
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
    use[k] = 0;
    if (res != flow)
        use[k] = 1;
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    cnt = ;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &l[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &r[i][j]);
    for (int i = 1; i <= m; ++i)
        rt[i] = build(1, n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
        }
    return 0;
}