#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, q, sum, cnt, tot;
int head[200005], fa[200005], val[200005], rt[200005];
int h[100005], hh[100005], lg[200005], dep[200005];
int f[200005][20];
struct node
{
    int v;
    int nxt;
} a[400005];
struct edge
{
    int u;
    int v;
    int w;
} b[500005];
struct tree
{
    int l;
    int r;
    int num;
} tr[20000005];
bool cmp(edge aa, edge bb)
{
    return aa.w < bb.w;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void add(int &x, int l, int r, int pos)
{
    x = ++tot;
    ++tr[x].num;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        add(tr[x].l, l, mid, pos);
    else
        add(tr[x].r, mid + 1, r, pos);
    return;
}
int merge(int x, int y, int l, int r)
{
    if (!x || !y)
        return x | y;
    int now = ++tot;
    if (l == r)
    {
        tr[now].num = tr[x].num + tr[y].num;
        return now;
    }
    int mid = (l + r) >> 1;
    tr[now].l = merge(tr[x].l, tr[y].l, l, mid);
    tr[now].r = merge(tr[x].r, tr[y].r, mid + 1, r);
    tr[now].num = tr[tr[now].l].num + tr[tr[now].r].num;
    return now;
}
int ask(int x, int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (tr[tr[x].l].num >= k)
        return ask(tr[x].l, l, mid, k);
    else
        return ask(tr[x].r, mid + 1, r, k - tr[tr[x].l].num);
}
void dfs(int k)
{
    for (int i = 1; i <= lg[dep[k]]; ++i)
        f[k][i] = f[f[k][i - 1]][i - 1];
    if (k <= n)
    {
        add(rt[k], 1, n, h[k]);
        return;
    }
    int d = head[k];
    while (d)
    {
        dep[a[d].v] = dep[k] + 1;
        dfs(a[d].v);
        rt[k] = merge(rt[k], rt[a[d].v], 1, n);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &q);
    cnt = n;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &h[i]);
        hh[i] = h[i];
    }
    for (int i = 1; i < 2 * n; ++i)
        fa[i] = i;
    sort(hh + 1, hh + n + 1);
    int len = unique(hh + 1, hh + n + 1) - hh - 1;
    for (int i = 1; i <= n; ++i)
        h[i] = lower_bound(hh + 1, hh + len + 1, h[i]) - hh;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &b[i].u, &b[i].v, &b[i].w);
    sort(b + 1, b + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        int u = getfather(b[i].u), v = getfather(b[i].v);
        if (u != v)
        {
            ++cnt;
            fa[u] = cnt;
            fa[v] = cnt;
            f[u][0] = cnt;
            f[v][0] = cnt;
            val[cnt] = b[i].w;
            ins(cnt, u);
            ins(cnt, v);
        }
    }
    for (int i = 2; i <= cnt; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= cnt; ++i)
        if (getfather(i) == i)
            dfs(i);
    for (int i = 1; i <= q; ++i)
    {
        int u, x, k;
        scanf("%d%d%d", &u, &x, &k);
        int d = u;
        for (int i = lg[dep[u]]; i >= 0; --i)
            if (f[d][i] && val[f[d][i]] <= x)
                d = f[d][i];
        if (tr[rt[d]].num < k)
            printf("-1\n");
        else
            printf("%d\n", hh[ask(rt[d], 1, n, tr[rt[d]].num - k + 1)]);
    }
    return 0;
}