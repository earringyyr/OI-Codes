#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf = 0x7f7f7f7f7f7f7f7f;
int n, m, s, t, sum = 1;
int head[205], cur[205], lev[205], l[205];
ll ans;
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
    for (int i = 1; i <= n; ++i)
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
ll dinic(int k, ll flow)
{
    if (k == t)
        return flow;
    ll delta, res = 0;
    int d = cur[k];
    while (d)
    {
        if (a[d].w > 0 && lev[a[d].v] == lev[k] + 1)
        {
            delta = dinic(a[d].v, min((ll)a[d].w, flow - res));
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
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
    }
    while (bfs())
        ans += dinic(s, inf);
    printf("%lld", ans);
    return 0;
}