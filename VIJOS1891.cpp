#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int inf = 0x7fffffff;
int n, k, s, ss, t, sum = 1, ans;
int head[1205], cur[1205], dis[1205], use[1205];
struct node
{
    int v;
    int w;
    int f;
    int nxt;
} a[500005];
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
    memset(dis, -1, sizeof(dis));
    for (int i = s; i <= t; ++i)
        cur[i] = head[i];
    int vis[1205] = {0};
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
            if (a[d].w > 0 && dis[a[d].v] < dis[k] + a[d].f)
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
    if (dis[t] != -1)
        return true;
    else
        return false;
}
inline int dinic(int k, int flow)
{
    if (k == t)
    {
        ans += dis[t] * flow;
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
    scanf("%d%d", &n, &k);
    s = 0;
    ss = 6 * n + 1;
    t = 6 * n + 2;
    ins(s, ss, k, 0);
    for (int i = 1; i <= 3 * n; ++i)
    {
        int x;
        scanf("%d", &x);
        ins(ss, i, 1, 0);
        ins(i, 3 * n + i, 1, x);
        ins(3 * n + i, t, 1, 0);
        for (int j = i + n; j <= 3 * n; ++j)
            ins(3 * n + i, j, 1, 0);
    }
    while (spfa())
        dinic(s, inf);
    printf("%d", ans);
    return 0;
}