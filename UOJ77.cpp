#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, s, t, num, cnt, sum = 1, ans;
int aa[50005], b[50005], w[50005], ll[50005], r[50005], p[50005];
int rt[50005], c[150005];
int head[50000005], cur[5000005], lev[5000005], l[5000005];
struct node
{
    int v;
    int w;
    int nxt;
} a[50000005];
struct tree
{
    int l;
    int r;
} tr[5000005];
inline void ins(int u, int v, int w)
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
inline void insert(int y, int &x, int l, int r, int L, int R, int type, int id)
{
    if (type)
    {
        x = ++cnt;
        tr[x] = tr[y];
    }
    if (!type && !y)
        return;
    if (l == L && r == R)
    {
        if (type)
        {
            if (L == R)
            {
                if (y)
                    ins(x, y, inf);
            }
            else
            {
                if (tr[x].l)
                    ins(x, tr[x].l, inf);
                if (tr[x].r)
                    ins(x, tr[x].r, inf);
            }
        }
        if (type == 0)
            ins(id, x, inf);
        else
            ins(x, id, inf);
        return;
    }
    int mid = (L + R) >> 1;
    if (r <= mid)
        insert(tr[y].l, tr[x].l, l, r, L, mid, type, id);
    if (l >= mid + 1)
        insert(tr[y].r, tr[x].r, l, r, mid + 1, R, type, id);
    if (l <= mid && r >= mid + 1)
    {
        insert(tr[y].l, tr[x].l, l, mid, L, mid, type, id);
        insert(tr[y].r, tr[x].r, mid + 1, r, mid + 1, R, type, id);
    }
    if (type)
    {
        if (tr[x].l)
            ins(x, tr[x].l, inf);
        if (tr[x].r)
            ins(x, tr[x].r, inf);
    }
    return;
}
inline bool bfs()
{
    memset(lev, -1, cnt * 4 + 4);
    memcpy(cur, head, cnt * 4 + 4);
    int hh = 0, tt = 1;
    lev[s] = 0;
    l[tt] = s;
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
    return lev[t] != -1;
}
inline int dinic(int k, int flow)
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
    scanf("%d", &n);
    s = 0;
    t = 2 * n + 1;
    cnt = 2 * n + 1;
    for (register int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d%d%d%d", &aa[i], &b[i], &w[i], &ll[i], &r[i], &p[i]);
        c[++num] = aa[i];
        c[++num] = ll[i];
        c[++num] = r[i];
    }
    sort(c + 1, c + num + 1);
    num = unique(c + 1, c + num + 1) - c - 1;
    for (register int i = 1; i <= n; ++i)
    {
        aa[i] = lower_bound(c + 1, c + num + 1, aa[i]) - c;
        ll[i] = lower_bound(c + 1, c + num + 1, ll[i]) - c;
        r[i] = lower_bound(c + 1, c + num + 1, r[i]) - c;
        ins(s, i, b[i]);
        ins(i, t, w[i]);
        ins(i, i + n, p[i]);
        insert(rt[i - 1], rt[i - 1], ll[i], r[i], 1, num, 0, i + n);
        insert(rt[i - 1], rt[i], aa[i], aa[i], 1, num, 1, i);
        ans += b[i] + w[i];
    }
    while (bfs())
        ans -= dinic(s, inf);
    printf("%d", ans);
    return 0;
}