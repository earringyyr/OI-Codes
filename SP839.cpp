#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, m, s, t, sum;
int val[505], head[505], cur[505], l[505], lev[505], ans[505];
struct edge
{
    int v;
    int w;
    int nxt;
} a[80005];
struct node
{
    int u;
    int v;
} q[3005];
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
    for (int i = s; i <= t; ++i)
    {
        cur[i] = head[i];
        lev[i] = -1;
    }
    int hh = 0, tt = 1;
    l[1] = s;
    lev[s] = 0;
    while (hh < tt)
    {
        int k = l[++hh];
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && lev[a[d].v] == -1)
            {
                lev[a[d].v] = lev[k] + 1;
                l[++tt] = a[d].v;
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
    int d = cur[k], delta, res = 0;
    while (d)
    {
        if (a[d].w > 0 && lev[a[d].v] == lev[k] + 1)
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
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(ans, 0, sizeof(ans));
        memset(val, -1, sizeof(val));
        scanf("%d%d", &n, &m);
        s = 0;
        t = n + 1;
        for (int i = 1; i <= m; ++i)
            scanf("%d%d", &q[i].u, &q[i].v);
        int k;
        scanf("%d", &k);
        for (int i = 1; i <= k; ++i)
        {
            int x;
            scanf("%d", &x);
            scanf("%d", &val[x]);
        }
        for (int i = 0; i < 31; ++i)
        {
            sum = 1;
            memset(head, 0, sizeof(head));
            for (int j = 1; j <= n; ++j)
                if (val[j] > 0)
                {
                    if ((1 << i) & val[j])
                        ins(s, j, inf);
                    else
                        ins(j, t, inf);
                }
            for (int j = 1; j <= m; ++j)
            {
                ins(q[j].u, q[j].v, 1);
                ins(q[j].v, q[j].u, 1);
            }
            while (bfs())
                dinic(s, inf);
            for (int j = 1; j <= n; ++j)
                if (lev[j] != -1)
                    ans[j] += (1 << i);
        }
        for (int i = 1; i <= n; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}