#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int inf = 0x7fffffff;
int n, m, sum = 1, s, t, ans;
int head[1005], cur[1005];
int vis[1005], dis[1005];
queue<int> q;
struct node
{
    int v;
    int w;
    int f;
    int nxt;
} a[40005];
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
        vis[i] = 0;
        dis[i] = inf;
        cur[i] = head[i];
    }
    q.push(s);
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
    return dis[t] != inf;
}
int dinic(int k, int flow)
{
    if (k == t)
    {
        ans += dis[k] * flow;
        return flow;
    }
    vis[k] = 1;
    int d = head[k], delta, res = 0;
    while (d)
    {
        if (!vis[a[d].v] && a[d].w > 0 && dis[k] + a[d].f == dis[a[d].v])
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
    vis[k] = 0;
    if (res != flow)
        vis[k] = 1;
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    s = 0;
    t = n + 1;
    ins(s, 1, inf, 0);
    for (int i = 1; i <= n; ++i)
    {
        int lst;
        scanf("%d", &lst);
        ins(i, i + 1, inf - lst, 0);
    }
    for (int i = 1; i <= m; ++i)
    {
        int S, T, C;
        scanf("%d%d%d", &S, &T, &C);
        ins(S, T + 1, inf, C);
    }
    while (spfa())
        dinic(s, inf);
    printf("%d", ans);
    return 0;
}