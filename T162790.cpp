#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7f7f7f7f;
int m, n, s, t, sum = 1, cnt, tot;
int c[60005], in[60005], out[60005];
int head[60005], cur[60005], lev[60005], l[60005];
struct edge
{
    int id;
    int v;
    int w;
    int nxt;
} a[240005];
struct node
{
    int l;
    int r;
    int w;
} b[30005];
void ins(int id, int u, int v, int w)
{
    ++sum;
    a[sum].id = id;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].id = id;
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
        lev[i] = -1;
        cur[i] = head[i];
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
    int delta, res = 0;
    int d = cur[k];
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
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &b[i].l, &b[i].r, &b[i].w);
        ++b[i].r;
        c[++cnt] = b[i].l;
        c[++cnt] = b[i].r;
    }
    sort(c + 1, c + cnt + 1);
    cnt = unique(c + 1, c + cnt + 1) - c - 1;
    s = 0;
    t = cnt + 1;
    for (int i = 1; i <= m; ++i)
    {
        b[i].l = lower_bound(c + 1, c + cnt + 1, b[i].l) - c;
        b[i].r = lower_bound(c + 1, c + cnt + 1, b[i].r) - c;
        if (b[i].w == 0)
        {
            ++out[b[i].l];
            ++in[b[i].r];
        }
        else if (b[i].w == 1)
        {
            ++in[b[i].l];
            ++out[b[i].r];
        }
        else
        {
            b[i].w = 0;
            ++out[b[i].l];
            ++in[b[i].r];
            ins(i, b[i].r, b[i].l, 1);
        }
    }
    for (int i = 1; i <= cnt; ++i)
    {
        if (in[i] > out[i])
        {
            if ((in[i] - out[i]) % 2 == 1)
            {
                ++out[i + 1];
                ++in[i];
                ins(0, i, i + 1, 1);
            }
            ins(0, s, i, (in[i] - out[i]) / 2);
            tot += (in[i] - out[i]) / 2;
        }
        if (in[i] < out[i])
        {
            if ((out[i] - in[i]) % 2 == 1)
            {
                ++out[i];
                ++in[i + 1];
                ins(0, i + 1, i, 1);
            }
            ins(0, i, t, (out[i] - in[i]) / 2);
        }
    }
    while (bfs())
        tot -= dinic(s, inf);
    if (tot > 0)
    {
        printf("-1");
        return 0;
    }
    for (int i = 2; i <= sum; i += 2)
        if (a[i].id && a[i].w == 0)
            b[a[i].id].w = 1;
    for (int i = 1; i <= m; ++i)
        printf("%d ", b[i].w);
    return 0;
}