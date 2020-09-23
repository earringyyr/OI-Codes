#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, m, k, s, t, sum = 1;
int num[255][255];
int head[70005], cur[70005], lev[70005], l[70005];
struct node
{
    int v;
    int w;
    int nxt;
} a[7000005];
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
    for (int i = s; i <= t + 2; ++i)
    {
        lev[i] = -1;
        cur[i] = head[i];
    }
    int hh = 0, tt = 1;
    lev[s] = 0;
    l[tt] = s;
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
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &num[i][j]);
    s = 0;
    t = n + m + 1;
    int l = 1, r = 1000000000;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        sum = 1;
        memset(head, 0, sizeof(head));
        for (int i = 1; i <= n; ++i)
            ins(s, i, 1);
        for (int i = 1; i <= m; ++i)
            ins(n + i, t, 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (num[i][j] <= mid)
                    ins(i, n + j, 1);
        int tot = 0;
        while (bfs())
            tot += dinic(s, inf);
        if (tot >= n - k + 1)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d", l);
    return 0;
}
