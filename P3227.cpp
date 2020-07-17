#include <iostream>
#include <cstdio>
#define inf 0x7fffffff
using namespace std;
int p, q, r, s, t, dd, ans, sum = 1, head[100005], lev[100005], cur[100005], f[50][50][50];
struct node
{
    int v;
    int w;
    int next;
} a[1000005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].next = head[v];
    head[v] = sum;
    return;
}
bool bfs()
{
    int hh = 0, tt = 1, q[100005];
    for (int i = s; i <= t; ++i)
    {
        lev[i] = -1;
        cur[i] = head[i];
    }
    q[1] = s;
    lev[s] = 0;
    while (hh < tt)
    {
        int k = q[++hh];
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && lev[a[d].v] == -1)
            {
                lev[a[d].v] = lev[k] + 1;
                q[++tt] = a[d].v;
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
        if (a[d].w > 0 && lev[k] < lev[a[d].v])
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
    scanf("%d%d%d%d", &p, &q, &r, &dd);
    s = 0;
    t = p * q * (r + 1) + 1;
    for (int i = 1; i <= p; ++i)
        for (int j = 1; j <= q; ++j)
        {
            ins(s, q * (i - 1) + j, inf);
            ins(p * q * r + q * (i - 1) + j, t, inf);
        }
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= p; ++j)
            for (int k = 1; k <= q; ++k)
            {
                scanf("%d", &f[i][j][k]);
                ins(p * q * (i - 1) + q * (j - 1) + k, p * q * i + q * (j - 1) + k, f[i][j][k]);
                if (i >= dd)
                {
                    if (k != q)
                        ins(p * q * i + q * (j - 1) + k, p * q * (i - dd) + q * (j - 1) + k + 1, inf);
                    if (k != 1)
                        ins(p * q * i + q * (j - 1) + k, p * q * (i - dd) + q * (j - 1) + k - 1, inf);
                    if (j != p)
                        ins(p * q * i + q * (j - 1) + k, p * q * (i - dd) + q * j + k, inf);
                    if (j != 1)
                        ins(p * q * i + q * (j - 1) + k, p * q * (i - dd) + q * (j - 2) + k, inf);
                }
            }
    while (bfs())
        ans += dinic(s, inf);
    printf("%d", ans);
    return 0;
}