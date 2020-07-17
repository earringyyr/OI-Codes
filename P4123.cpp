#include <iostream>
#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;
int n, m, sum = 1, s, t;
int head[1005], cur[1005], lev[1005], ss[1005];
set<int> st;
struct node
{
    int v;
    int w;
    int nxt;
} a[20005], b[20005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    ++sum;
    a[sum].v = u;
    a[sum].w = w;
    a[sum].nxt = head[v];
    head[v] = sum;
    return;
}
bool bfs()
{
    for (int i = 1; i <= n; ++i)
    {
        cur[i] = head[i];
        lev[i] = -1;
    }
    int hh = 0, tt = 1, l[1005];
    l[1] = s;
    lev[s] = 0;
    while (hh < tt)
    {
        ++hh;
        int k = l[hh];
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
    int d = cur[k], res = 0, delta;
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
bool cmp(int aa, int bb)
{
    return lev[aa] < lev[bb];
}
void solve(int l, int r)
{
    if (l == r)
        return;
    s = ss[l];
    t = ss[r];
    int res = 0, mid;
    while (bfs())
        res += dinic(s, inf);
    st.insert(res);
    sort(ss + l, ss + r + 1, cmp);
    for (int i = l; i <= r; ++i)
        if (lev[ss[i]] != -1)
        {
            mid = i - 1;
            break;
        }
    memcpy(a, b, sizeof(b));
    solve(l, mid);
    solve(mid + 1, r);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
    }
    memcpy(b, a, sizeof(a));
    for (int i = 1; i <= n; ++i)
        ss[i] = i;
    solve(1, n);
    int ans = st.size();
    printf("%d", ans);
    return 0;
}