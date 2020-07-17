#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
int n, Q, s, t, sum = 1, xx, yy;
int numx[2505], numy[2505], ans[10005], q[30000005];
int vis[5005], dis[5005], cur[5005], use[5005], head[5005];
int x[55][55], y[55][55];
char mp[55][55];
struct node
{
    int v;
    int w;
    int f;
    int nxt;
} a[20005];
struct point
{
    int id;
    int k;
} st[10005];
bool cmp(point aa, point bb)
{
    return aa.k < bb.k;
}
void ins(int u, int v, int w, int f)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].f = f;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = 0;
    a[sum].f = -f;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
void spfa()
{
    memset(use, 0, sizeof(use));
    memset(dis, 0x3f, sizeof(dis));
    int hhead = 0, ttail = 1, vis[5005] = {0};
    for (int i = s; i <= t; ++i)
        cur[i] = head[i];
    q[1] = s;
    vis[s] = 1;
    dis[s] = 0;
    while (hhead < ttail)
    {
        ++hhead;
        int k = q[hhead];
        vis[k] = 0;
        int d = head[k];
        while (d)
        {
            if (a[d].w > 0 && dis[a[d].v] > dis[k] + a[d].f)
            {
                dis[a[d].v] = dis[k] + a[d].f;
                if (!vis[a[d].v])
                {
                    q[++ttail] = a[d].v;
                    vis[a[d].v] = 1;
                }
            }
            d = a[d].nxt;
        }
    }
    return;
}
int dinic(int k, int flow)
{
    if (k == t)
    {
        ans[0] += dis[t] * flow;
        return flow;
    }
    use[k] = 1;
    int d = cur[k], res = 0, delta;
    while (d)
    {
        if (!use[a[d].v] && a[d].w > 0 && dis[k] + a[d].f == dis[a[d].v])
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
    use[k] = 0;
    if (res != flow)
        use[k] = 1;
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (mp[i][j] == '.')
            {
                if (mp[i][j - 1] != '.')
                    x[i][j] = ++xx;
                else
                    x[i][j] = x[i][j - 1];
                if (mp[i - 1][j] != '.')
                    y[i][j] = ++yy;
                else
                    y[i][j] = y[i - 1][j];
                ++numx[x[i][j]];
                ++numy[y[i][j]];
            }
    t = xx + yy + 1;
    for (int i = 1; i <= xx; ++i)
        for (int j = 0; j < numx[i]; ++j)
            ins(s, i, 1, j);
    for (int i = 1; i <= yy; ++i)
        for (int j = 0; j < numy[i]; ++j)
            ins(xx + i, t, 1, j);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (mp[i][j] == '.')
                ins(x[i][j], xx + y[i][j], 1, 0);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i)
    {
        st[i].id = i;
        scanf("%d", &st[i].k);
    }
    sort(st + 1, st + Q + 1, cmp);
    st[0].k = 0;
    for (int i = 1; i <= Q; ++i)
    {
        int res = st[i].k - st[i - 1].k;
        while (res)
        {
            spfa();
            res -= dinic(s, res);
        }
        ans[st[i].id] = ans[0];
    }
    for (int i = 1; i <= Q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}