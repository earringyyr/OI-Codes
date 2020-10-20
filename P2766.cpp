#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
int n, s, t, sum = 1, maxn, ans;
int x[505], f[505];
int head[1005], cur[1005], lev[1005], q[1005];
struct node
{
    int v;
    int w;
    int nxt;
} a[10005];
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
    int hh = 0, tt = 1;
    for (int i = s; i <= t; ++i)
    {
        lev[i] = -1;
        cur[i] = head[i];
    }
    q[1] = s;
    lev[s] = 0;
    while (hh < tt)
    {
        ++hh;
        int k = q[hh];
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
int main()
{
    scanf("%d", &n);
    s = 0;
    t = 2 * n + 1;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &x[i]);
    for (int i = 1; i <= n; ++i)
    {
        f[i] = 1;
        for (int j = 1; j < i; ++j)
            if (x[j] <= x[i])
                f[i] = max(f[i], f[j] + 1);
        if (f[i] > maxn)
            maxn = f[i];
    }
    printf("%d\n", maxn);
    for (int i = 1; i <= n; ++i)
    {
        ins(i, i + n, 1);
        if (f[i] == 1)
            ins(s, i, 1);
        if (f[i] == maxn)
            ins(i + n, t, 1);
        for (int j = 1; j < i; ++j)
            if (x[i] >= x[j] && f[i] == f[j] + 1)
                ins(j + n, i, 1);
    }
    while (bfs())
        ans += dinic(s, inf);
    printf("%d\n", ans);
    if (n == 1)
    {
        printf("1");
        return 0;
    }
    ans = 0;
    sum = 1;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= n; ++i)
    {
        if (i == 1 || i == n)
            ins(i, i + n, inf);
        else
            ins(i, i + n, 1);
        if (f[i] == 1)
            if (i == 1)
                ins(s, i, inf);
            else
                ins(s, i, 1);
        if (f[i] == maxn)
            if (i == n)
                ins(i + n, t, inf);
            else
                ins(i + n, t, 1);
        for (int j = 1; j < i; ++j)
            if (x[i] >= x[j] && f[i] == f[j] + 1)
                ins(j + n, i, 1);
    }
    while (bfs())
        ans += dinic(s, inf);
    printf("%d", ans);
    return 0;
}