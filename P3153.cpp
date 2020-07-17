#include <iostream>
#include <cstdio>
#include <cstring>
#define inf 0x7fffffff
using namespace std;
int n, K, s, t, sum;
int vis[55][55], head[305];
int lev[305], cur[305];
struct node
{
    int v;
    int w;
    int nxt;
} a[200005];
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
    int hhead = 0, ttail = 1, q[305];
    for (int i = s; i <= t; ++i)
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
            }
            d = a[d].nxt;
        }
    }
    if (lev[t] != -1)
        return true;
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
bool check(int mid)
{
    sum = 1;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= n; ++i)
    {
        ins(s, i, mid);
        ins(i, n + i, K);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (vis[i][j])
                ins(i, 3 * n + j, 1);
            else
                ins(n + i, 2 * n + j, 1);
    for (int i = 1; i <= n; ++i)
    {
        ins(3 * n + i, t, mid);
        ins(2 * n + i, 3 * n + i, K);
    }
    int ans = 0;
    while (bfs())
        ans += dinic(s, inf);
    return ans == n * mid;
}
int main()
{
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            char ch;
            scanf(" %c", &ch);
            if (ch == 'Y')
                vis[i][j] = 1;
        }
    s = 0;
    t = 4 * n + 1;
    int lef = 0, rig = n;
    while (lef < rig)
    {
        int mid = (lef + rig + 1) >> 1;
        if (check(mid))
            lef = mid;
        else
            rig = mid - 1;
    }
    printf("%d", lef);
    return 0;
}