#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;
int n, m, sum, top, h, t, lg[50005], pos[50005], dep[50005], vis[50005], use[50005], head[50005], q[50005], qq[50005], fa[20][50005], dis[20][50005];
bool p = false;
struct node
{
    int v;
    int w;
    int nxt;
} a[100005];
struct point
{
    int id;
    int lim;
    point(int aa = 0, int bb = 0)
    {
        id = aa;
        lim = bb;
    }
} s[50005];
bool cmp(point aa, point bb)
{
    return aa.lim < bb.lim;
}
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k)
{
    for (int i = 1; i <= lg[dep[k]]; ++i)
    {
        fa[i][k] = fa[i - 1][fa[i - 1][k]];
        dis[i][k] = dis[i - 1][k] + dis[i - 1][fa[i - 1][k]];
    }
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[0][k])
        {
            dep[a[d].v] = dep[k] + 1;
            fa[0][a[d].v] = k;
            dis[0][a[d].v] = a[d].w;
            dfs1(a[d].v);
        }
        d = a[d].nxt;
    }
    return;
}
bool dfs2(int k)
{
    bool pp = false;
    if (vis[k])
        return 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[0][k])
        {
            pp = true;
            if (!dfs2(a[d].v))
                return 0;
        }
        d = a[d].nxt;
    }
    if (!pp)
        return 0;
    return 1;
}
bool check(int k)
{
    top = 0;
    h = 0;
    t = 0;
    memset(vis, 0, sizeof(vis));
    memset(use, 0, sizeof(use));
    for (int i = 1; i <= m; ++i)
    {
        int id = pos[i], cnt = 0;
        for (int j = lg[dep[pos[i]]]; j >= 0; --j)
            if (fa[j][id] > 1 && dis[j][id] + cnt <= k)
            {
                cnt += dis[j][id];
                id = fa[j][id];
            }
        if (fa[0][id] == 1 && cnt + dis[0][id] <= k)
            s[++top] = point(id, k - cnt - dis[0][id]);
        else
            vis[id] = 1;
    }
    int d = head[1];
    while (d)
    {
        if (!dfs2(a[d].v))
            use[a[d].v] = 1;
        d = a[d].nxt;
    }
    sort(s + 1, s + top + 1, cmp);
    for (int i = 1; i <= top; ++i)
        if (use[s[i].id] && s[i].lim < dis[0][s[i].id])
            use[s[i].id] = 0;
        else
            q[++t] = s[i].lim;
    d = head[1];
    while (d)
    {
        if (use[a[d].v])
            qq[++h] = a[d].w;
        d = a[d].nxt;
    }
    sort(qq + 1, qq + h + 1);
    int j = 1;
    for (int i = 1; i <= h; ++i)
    {
        while (j <= t && q[j] < qq[i])
            ++j;
        if (j >= t + 1)
            return false;
        ++j;
    }
    return true;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    dep[1] = 1;
    dfs1(1);
    scanf("%lld", &m);
    for (int i = 1; i <= m; ++i)
        scanf("%lld", &pos[i]);
    int lef = 0, rig = 500000000000000;
    while (lef < rig)
    {
        int mid = (lef + rig) >> 1;
        if (check(mid))
        {
            rig = mid;
            p = true;
        }
        else
            lef = mid + 1;
    }
    if (p)
        printf("%lld", lef);
    else
        printf("-1");
    return 0;
}