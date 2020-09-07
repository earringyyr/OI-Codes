#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, sum = 1, s, t, ans;
int head[3005], A[3005];
int vis[200005], pri[200005];
int l[3005], lev[3005], cur[3005];
struct node
{
    int v;
    int w;
    int nxt;
} a[20000005];
bool cmp(int aa, int bb)
{
    return aa > bb;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = 1;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
int bfs()
{
    for (int i = s; i <= t; ++i)
    {
        lev[i] = -1;
        cur[i] = head[i];
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
    for (int i = 2; i <= 200000; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
        }
        for (int j = 1; j <= sum && vis[i] >= pri[j] && pri[j] * i <= 200000; ++j)
            vis[pri[j] * i] = pri[j];
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &A[i]);
    sort(A + 1, A + n + 1, cmp);
    while (n > 1 && A[n] == A[n - 1] && A[n] == 1)
        --n;
    s = 0;
    t = n + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (vis[A[i] + A[j]] == A[i] + A[j])
            {
                if (A[i] % 2 == 0)
                    ins(i, j);
                else
                    ins(j, i);
            }
    for (int i = 1; i <= n; ++i)
        if (A[i] % 2 == 0)
            ins(s, i);
        else
            ins(i, t);
    ans = n;
    while (bfs())
        ans -= dinic(s, inf);
    printf("%d", ans);
    return 0;
}