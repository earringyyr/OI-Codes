#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, K, s, t, T, sum = 1;
int fa[25], h[25], r[25];
int head[40005], cur[40005], lev[40005];
int l[40005];
int pos[25][25];
struct node
{
    int v;
    int w;
    int nxt;
} a[100005];
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
    return;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
bool bfs()
{
    for (int i = 0; i <= (T + 1) * (n + 2); ++i)
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
                if (a[d].v == t)
                    return 1;
            }
            d = a[d].nxt;
        }
    }
    return 0;
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
    s = 1;
    t = 0;
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i <= n + 1; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &h[i], &r[i]);
        for (int j = 1; j <= r[i]; ++j)
        {
            scanf("%d", &pos[i][j]);
            if (pos[i][j] == -1)
                pos[i][j] = n + 1;
            if (j != 1)
                if (getfather(pos[i][j - 1]) != getfather(pos[i][j]))
                    fa[getfather(pos[i][j - 1])] = getfather(pos[i][j]);
        }
    }
    if (getfather(0) != getfather(n + 1))
    {
        printf("0");
        return 0;
    }
    ins(n + 2, t, inf);
    while (1)
    {
        ++T;
        for (int i = 0; i <= n + 1; ++i)
            ins((T - 1) * (n + 2) + i + 1, T * (n + 2) + i + 1, inf);
        ins(T * (n + 2) + n + 2, t, inf);
        for (int i = 1; i <= m; ++i)
            if (T % r[i] == 0)
                ins((T - 1) * (n + 2) + pos[i][r[i]] + 1, T * (n + 2) + pos[i][1] + 1, h[i]);
            else
                ins((T - 1) * (n + 2) + pos[i][T % r[i]] + 1, T * (n + 2) + pos[i][T % r[i] + 1] + 1, h[i]);
        while (bfs())
            K -= dinic(s, inf);
        if (K <= 0)
        {
            printf("%d", T);
            break;
        }
    }
    return 0;
}