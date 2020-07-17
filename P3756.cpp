#include <iostream>
#include <cstdio>
#include <tr1/unordered_map>
#define inf 0x7fffffff
using namespace std;
using namespace tr1;
typedef long long ll;
int c, r, n, s, t, ans, sum = 1;
int head[100005], lev[100005], cur[100005], co[100005];
int x[100005], y[100005], w[100005];
int gox[4] = {0, 0, 1, -1}, goy[4] = {1, -1, 0, 0};
unordered_map<ll, int> mp;
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
    scanf("%d%d%d", &c, &r, &n);
    s = 0;
    t = n + 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
        if (x[i] % 4 == 0 && y[i] % 2 == 0)
            co[i] = 1;
        else if (x[i] % 4 == 0 && y[i] % 2 == 1)
            co[i] = 3;
        else if (x[i] % 4 == 1 && y[i] % 2 == 0)
            co[i] = 3;
        else if (x[i] % 4 == 1 && y[i] % 2 == 1)
            co[i] = 1;
        else if (x[i] % 4 == 2 && y[i] % 2 == 0)
            co[i] = 4;
        else if (x[i] % 4 == 2 && y[i] % 2 == 1)
            co[i] = 2;
        else if (x[i] % 4 == 3 && y[i] % 2 == 0)
            co[i] = 2;
        else if (x[i] % 4 == 3 && y[i] % 2 == 1)
            co[i] = 4;
        mp[(ll)(x[i] - 1) * (c + 1) + y[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        if (co[i] == 1)
            for (int j = 0; j < 4; ++j)
            {
                int xx = x[i] + gox[j], yy = y[i] + goy[j];
                int col = mp[(ll)(xx - 1) * (c + 1) + yy];
                if (col)
                {
                    if (co[col] != 2)
                        ins(col, i, inf);
                    else
                        ins(i, col, min(w[i], w[col]));
                }
            }
        else if (co[i] == 2)
            for (int j = 0; j < 4; ++j)
            {
                int xx = x[i] + gox[j], yy = y[i] + goy[j];
                int col = mp[(ll)(xx - 1) * (c + 1) + yy];
                if (col && co[col] != 1)
                    ins(i, col, inf);
            }
        else if (co[i] == 3)
            ins(s, i, w[i]);
        else if (co[i] == 4)
            ins(i, t, w[i]);
    while (bfs())
        ans += dinic(s, inf);
    printf("%d", ans);
    return 0;
}