#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x7f7f7f7f
using namespace std;
int n, m, s, t, sum = 1, ans, cost;
int head[5005], cur[5005], dis[5005], use[5005];
struct node
{
    int v;
    int w;
    int f;
    int nxt;
} a[100005];
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
    for (int i = 1; i <= n; ++i)
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
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w, f;
        scanf("%d%d%d%d", &u, &v, &w, &f);
        ins(u, v, w, f);
    }
    while (spfa())
        ans += dinic(s, inf);
    printf("%d %d", ans, cost);
    return 0;
}