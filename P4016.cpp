#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define inf 0x7fffffff
using namespace std;
int n, s, t, sum = 1, tot, ans, A[105], head[105], d[105], use[105], cur[105];
struct node
{
    int v;
    int w;
    int f;
    int nxt;
} a[100005];
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
    memset(use, 0, sizeof(use));
    memset(d, 0x3f, sizeof(d));
    for (int i = s; i <= t; ++i)
        cur[i] = head[i];
    int hhead = 0, ttail = 1, q[10005], vis[105] = {0};
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
            dd = a[dd].nxt;
        }
    }
    if (d[t] < inf)
        return true;
    else
        return false;
}
int dinic(int k, int flow)
{
    if (k == t)
    {
        ans += d[t] * flow;
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
        dd = a[dd].nxt;
        cur[k] = dd;
    }
    use[k] = 0;
    if (res != flow)
        use[k] = 1;
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &A[i]);
        tot += A[i];
    }
    tot /= n;
    s = 0;
    t = n + 1;
    for (int i = 1; i <= n; ++i)
    {
        ins(s, i, A[i], 0);
        ins(i, t, tot, 0);
        for (int j = 1; j <= n; ++j)
            if (i != j)
                ins(i, j, inf, min(abs(i - j), n - abs(i - j)));
    }
    while (spfa())
    {
        int p = dinic(s, inf);
        if (!p)
            break;
    }
    printf("%d", ans);
    return 0;
}