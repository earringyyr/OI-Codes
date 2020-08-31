#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
int n, m, s, t, ans, sum;
int out[605], vis[605], q[605];
int val[25][35], w[25][35];
int x[25][35][605], y[25][35][605];
int head[605], lev[605], cur[605];
struct node
{
    int v;
    int w;
    int nxt;
} a[720005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void ins2(int u, int v, int w)
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
    int hhead = 0, ttail = 1;
    for (int i = 0; i <= t; ++i)
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
            d = a[d].nxt;
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
        d = a[d].nxt;
        cur[k] = d;
    }
    if (res != flow)
        lev[k] = -1;
    return res;
}
signed main()
{
    scanf("%d%d", &n, &m);
    s = n * m;
    t = n * m + 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &val[i][j]);
            if (j)
            {
                ins(i * m + j, i * m + j - 1);
                ++out[i * m + j - 1];
            }
            scanf("%d", &w[i][j]);
            for (int k = 1; k <= w[i][j]; ++k)
            {
                scanf("%d%d", &x[i][j][k], &y[i][j][k]);
                ins(i * m + j, x[i][j][k] * m + y[i][j][k]);
                ++out[x[i][j][k] * m + y[i][j][k]];
            }
        }
    int hhead = 0, ttail = 0;
    for (int i = 0; i < n * m; ++i)
        if (!out[i])
        {
            q[++ttail] = i;
            vis[i] = 1;
        }
    while (hhead < ttail)
    {
        int k = q[++hhead];
        int d = head[k];
        while (d)
        {
            --out[a[d].v];
            if (!out[a[d].v])
            {
                q[++ttail] = a[d].v;
                vis[a[d].v] = 1;
            }
            d = a[d].nxt;
        }
    }
    sum = 1;
    memset(head, 0, sizeof(head));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (vis[i * m + j])
            {
                if (val[i][j] > 0)
                {
                    ans += val[i][j];
                    ins2(s, i * m + j, val[i][j]);
                }
                else
                    ins2(i * m + j, t, -val[i][j]);
                if (j && vis[i * m + j - 1])
                    ins2(i * m + j - 1, i * m + j, inf);
                for (int k = 1; k <= w[i][j]; ++k)
                    if (vis[x[i][j][k] * m + y[i][j][k]])
                        ins2(x[i][j][k] * m + y[i][j][k], i * m + j, inf);
            }
    while (bfs())
        ans -= dinic(s, inf);
    ans = max(0, ans);
    printf("%d", ans);
    return 0;
}