#include <iostream>
#include <cstdio>
#define inf 0x7fffffff
using namespace std;
int n, s, t, sum = 1, ans;
int b[505][505], c[505];
int head[2500005], lev[2500005], cur[2500005];
struct node
{
    int v;
    int w;
    int nxt;
} a[30000005];
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
    int hhead = 0, ttail = 1, q[2500005];
    for (int i = s; i <= t; ++i)
    {
        lev[i] = -1;
        cur[i] = head[i];
    }
    q[1] = s;
    lev[s] = 0;
    while (hhead < ttail)
    {
        ++hhead;
        int k = q[hhead];
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && lev[a[d].v] == -1)
            {
                lev[a[d].v] = lev[k] + 1;
                q[++ttail] = a[d].v;
            }
            d = a[d].nxt;
        }
    }
    return lev[t] != -1;
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
int main()
{
    scanf("%d", &n);
    s = 0;
    t = n * (n + 1) + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &b[i][j]);
            ins(i * n + j, t, b[i][j]);
            ins(i, i * n + j, inf);
            ins(j, i * n + j, inf);
            ans += b[i][j];
        }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
        ins(s, i, c[i]);
    }
    while (bfs())
        ans -= dinic(s, inf);
    printf("%d", ans);
    return 0;
}