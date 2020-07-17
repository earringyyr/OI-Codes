#include <iostream>
#include <cstdio>
#define inf 0x7fffffff
using namespace std;
int n, m, s, t, ans, sum = 1, head[10005], lev[100005], cur[100005];
struct node
{
    int v;
    int w;
    int next;
} a[200005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool bfs()
{
    int hhead = 0, ttail = 1, q[100005];
    for (int i = 1; i <= n; ++i)
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
                if (a[d].v == t)
                    return true;
            }
            d = a[d].next;
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
        d = a[d].next;
        cur[k] = d;
    }
    if (res != flow)
        lev[k] = -1;
    return res;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, 0);
    }
    while (bfs())
        ans += dinic(s, inf);
    printf("%d", ans);
    return 0;
}