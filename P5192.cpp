#include <iostream>
#include <cstdio>
#include <cstring>
#define inf 0x7fffffff
using namespace std;
int n, m, s, t, sum, num, ans;
int c[505], d[505];
int g[1005];
int head[1505], cur[1505], lev[1505], l[1505], in[1505], out[1505];
int T[505][1005], L[505][1005], R[505][1005];
struct node
{
    int v;
    int w;
    int nxt;
} a[2000005];
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
    for (int i = 0; i <= n + m + 3; ++i)
    {
        cur[i] = head[i];
        lev[i] = -1;
    }
    int hh = 0, tt = 1;
    l[tt] = s;
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
    while (~scanf("%d%d", &n, &m))
    {
        sum = 1;
        ans = 0;
        num = 0;
        memset(head, 0, sizeof(head));
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        s = 0;
        t = n + m + 1;
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d", &g[i]);
            in[t] += g[i];
            out[n + i] += g[i];
            ins(n + i, t, inf);
        }
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d%d", &c[i], &d[i]);
            ins(s, i, d[i]);
            for (int j = 1; j <= c[i]; ++j)
            {
                scanf("%d%d%d", &T[i][j], &L[i][j], &R[i][j]);
                ++T[i][j];
                out[i] += L[i][j];
                in[n + T[i][j]] += L[i][j];
                ins(i, n + T[i][j], R[i][j] - L[i][j]);
            }
        }
        s = n + m + 2;
        t = n + m + 3;
        for (int i = 0; i <= n + m + 1; ++i)
        {
            if (in[i] > out[i])
            {
                ins(s, i, in[i] - out[i]);
                num += in[i] - out[i];
            }
            if (in[i] < out[i])
                ins(i, t, out[i] - in[i]);
        }
        ins(n + m + 1, 0, inf);
        while (bfs())
            num -= dinic(s, inf);
        if (num)
        {
            printf("-1\n\n");
            continue;
        }
        s = 0;
        t = n + m + 1;
        while (bfs())
            ans += dinic(s, inf);
        printf("%d\n\n", ans);
    }
    return 0;
}