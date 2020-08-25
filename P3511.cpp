#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, m, sum, s, t, top;
int lev[1005], cur[1005];
int ans[20005];
int go[1005][1005];
int head[1005], fa[1005], in[1005], out[1005];
int u[20005], v[20005], l[20005], p[20005];
struct node
{
    int v;
    int w;
    int nxt;
} a[42005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
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
void insert(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool bfs()
{
    for (int i = s; i <= t; ++i)
    {
        cur[i] = head[i];
        lev[i] = -1;
    }
    int hh = 0, tt = 0, l[1005];
    l[++tt] = s;
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
bool check(int mid)
{
    sum = 1;
    memset(head, 0, sizeof(head));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for (int i = 1; i <= m; ++i)
    {
        if (l[i] <= mid && p[i] <= mid)
        {
            ins(v[i], u[i], 1);
            ++out[u[i]];
            ++in[v[i]];
        }
        else if (l[i] <= mid)
        {
            ++out[u[i]];
            ++in[v[i]];
        }
        else
        {
            ++in[u[i]];
            ++out[v[i]];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (abs(in[i] - out[i]) % 2 != 0)
            return false;
        if (in[i] > out[i])
            ins(s, i, (in[i] - out[i]) / 2);
        if (in[i] < out[i])
            ins(i, t, (out[i] - in[i]) / 2);
    }
    while (bfs())
        dinic(s, inf);
    int d = head[s];
    while (d)
    {
        if (a[d].w != 0)
            return false;
        d = a[d].nxt;
    }
    return true;
}
void dfs(int k)
{
    int d = head[k];
    while (d)
    {
        head[k] = a[d].nxt;
        dfs(a[d].v);
        ans[++top] = a[d].w;
        d = head[k];
    }
    return;
}
int main()
{
    int lef = 0, rig = 0;
    scanf("%d%d", &n, &m);
    s = 0;
    t = n + 1;
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d%d", &u[i], &v[i], &l[i], &p[i]);
        lef = max(lef, min(l[i], p[i]));
        rig = max(rig, max(l[i], p[i]));
        if (getfather(u[i]) != getfather(v[i]))
            fa[getfather(u[i])] = getfather(v[i]);
        ++in[u[i]];
        ++in[v[i]];
    }
    int tmp;
    for (int i = 1; i <= n; ++i)
        if (in[i])
        {
            tmp = getfather(i);
            break;
        }
    for (int i = 1; i <= n; ++i)
        if (in[i] && getfather(i) != tmp)
        {
            printf("NIE");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        if (in[i] % 2 != 0)
        {
            printf("NIE");
            return 0;
        }
    while (lef < rig)
    {
        int mid = (lef + rig) >> 1;
        if (check(mid))
            rig = mid;
        else
            lef = mid + 1;
    }
    sum = 1;
    memset(head, 0, sizeof(head));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for (int i = 1; i <= m; ++i)
    {
        if (l[i] <= lef && p[i] <= lef)
        {
            ins(v[i], u[i], 1);
            go[u[i]][v[i]] = i;
            ++out[u[i]];
            ++in[v[i]];
        }
        else if (l[i] <= lef)
        {
            go[u[i]][v[i]] = i;
            ++out[u[i]];
            ++in[v[i]];
        }
        else
        {
            go[v[i]][u[i]] = i;
            ++in[u[i]];
            ++out[v[i]];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (in[i] > out[i])
            ins(s, i, (in[i] - out[i]) / 2);
        if (in[i] < out[i])
            ins(i, t, (out[i] - in[i]) / 2);
    }
    while (bfs())
        dinic(s, inf);
    for (int i = 1; i <= n; ++i)
    {
        int d = head[i];
        while (d)
        {
            if (a[d].v != s && a[d].v != t && d % 2 == 0 && !a[d].w)
            {
                go[i][a[d].v] = go[a[d].v][i];
                go[a[d].v][i] = 0;
            }
            d = a[d].nxt;
        }
    }
    sum = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (go[i][j])
                insert(i, j, go[i][j]);
    for (int i = 1; i <= n; ++i)
        if (head[i])
        {
            dfs(i);
            break;
        }
    printf("%d\n", lef);
    for (int i = m; i >= 1; --i)
        printf("%d ", ans[i]);
    return 0;
}