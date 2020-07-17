#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
#define inf 0x7f7f7f7f
using namespace std;
int n, p, m, f, nn, ss, s, t, sum = 1, ans, cost, head[4005], d[4005], use[4005], num[4005];
struct node
{
    int v;
    int w;
    int f;
    int next;
} a[25005];
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
    memset(d, 0x7f, sizeof(d));
    int hhead = 0, ttail = 1, q[16000005], vis[4005] = {0};
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
    int dd = head[k], res = 0, delta;
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
    }
    return res;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &num[i]);
        ins(1, i + 1, num[i], 0);
        ins(i + 1, 1, 0, 0);
        ins(i + n + 1, 2 * n + 2, num[i], 0);
        ins(2 * n + 2, i + n + 1, 0, 0);
    }
    scanf("%lld%lld%lld%lld%lld", &p, &m, &f, &nn, &ss);
    for (int i = 1; i <= n; ++i)
    {
        ins(1, i + n + 1, inf, p);
        ins(i + n + 1, 1, 0, -p);
        if (i + 1 <= n)
        {
            ins(i + 1, i + 2, inf, 0);
            ins(i + 2, i + 1, 0, 0);
        }
        if (i + m <= n)
        {
            ins(i + 1, i + m + n + 1, inf, f);
            ins(i + m + n + 1, i + 1, 0, -f);
        }
        if (i + nn <= n)
        {
            ins(i + 1, i + nn + n + 1, inf, ss);
            ins(i + nn + n + 1, i + 1, 0, -ss);
        }
    }
    s = 1;
    t = 2 * n + 2;
    while (spfa())
        ans += dinic(s, inf);
    printf("%lld", cost);
    return 0;
}