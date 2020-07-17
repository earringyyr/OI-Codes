#include <iostream>
#include <cstdio>
#define inf 0x7fffffff
using namespace std;
typedef long long ll;
int n, m, s, t, sum = 1, cnt, ans;
int head[100005], lev[100005], cur[100005];
int ar[105][105], sc[105][105], sar[105][105], ssc[105][105];
int gox[4] = {0, 0, 1, -1}, goy[4] = {1, -1, 0, 0};
struct node
{
    int v;
    int w;
    int nxt;
} a[500005];
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
    int hhead = 0, ttail = 1, q[100005];
    for (int i = s; i <= cnt; ++i)
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
    return lev[t] != -1;
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
    scanf("%d%d", &n, &m);
    s = 0;
    t = n * m + 1;
    cnt = n * m + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &ar[i][j]);
            ans += ar[i][j];
            ins(s, (i - 1) * m + j, ar[i][j]);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &sc[i][j]);
            ans += sc[i][j];
            ins((i - 1) * m + j, t, sc[i][j]);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &sar[i][j]);
            ans += sar[i][j];
            ++cnt;
            ins(s, cnt, sar[i][j]);
            ins(cnt, (i - 1) * m + j, inf);
            for (int k = 0; k < 4; ++k)
                if (i + gox[k] >= 1 && i + gox[k] <= n && j + goy[k] >= 1 && j + goy[k] <= m)
                    ins(cnt, (i + gox[k] - 1) * m + j + goy[k], inf);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &ssc[i][j]);
            ans += ssc[i][j];
            ++cnt;
            ins(cnt, t, ssc[i][j]);
            ins((i - 1) * m + j, cnt, inf);
            for (int k = 0; k < 4; ++k)
                if (i + gox[k] >= 1 && i + gox[k] <= n && j + goy[k] >= 1 && j + goy[k] <= m)
                    ins((i + gox[k] - 1) * m + j + goy[k], cnt, inf);
        }
    while (bfs())
        ans -= dinic(s, inf);
    printf("%d", ans);
    return 0;
}