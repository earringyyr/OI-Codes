#include <iostream>
#include <cstdio>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;
int n, m, s, t, sum = 1, ans, cost, head[5005], d[5005], use[5005], cur[5005];
struct node
{
    int v;
    int w;
    int f;
    int next;
} a[100005];
inline void ins(int u, int v, int w, int f)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].f = f;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
inline bool spfa()
{
    memset(use, 0, sizeof(use));
    memset(d, 0x3f, sizeof(d));
    for (int i = 1; i <= n; ++i)
        cur[i] = head[i];
    int hhead = 0, ttail = 1, q[25000005], vis[5005] = {0};
    q[1] = s;
    vis[s] = 1;
    d[s] = 0;
    while (hhead < ttail)
    {
        ++hhead;
        int k = q[hhead];
        vis[k] = 0;
        int dd = head[k];
        while (dd)
        {
            if (a[dd].w > 0 && d[a[dd].v] > d[k] + a[dd].f)
            {
                d[a[dd].v] = d[k] + a[dd].f;
                if (!vis[a[dd].v])
                {
                    q[++ttail] = a[dd].v;
                    vis[a[dd].v] = 1;
                }
            }
            dd = a[dd].next;
        }
    }
    if (d[t] < inf)
        return true;
    else
        return false;
}
inline int dinic(int k, int flow)
{
    if (k == t)
    {
        cost += d[t] * flow;
        return flow;
    }
    use[k] = 1;
    int dd = cur[k], res = 0, delta;
    while (dd)
    {
        if (!use[a[dd].v] && a[dd].w > 0 && d[k] + a[dd].f == d[a[dd].v])
        {
            delta = dinic(a[dd].v, min(a[dd].w, flow - res));
            if (delta)
            {
                a[dd].w -= delta;
                a[dd ^ 1].w += delta;
                res += delta;
                if (res == flow)
                    break;
            }
        }
        dd = a[dd].next;
        cur[k] = dd;
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
        ins(v, u, 0, -f);
    }
    while (spfa())
        ans += dinic(s, inf);
    printf("%d %d", ans, cost);
    return 0;
}