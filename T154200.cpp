#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, type, q, cnt, sum, num, ans;
int c[150005];
int fa[400005], head[400005];
int val[400005], rt[400005], cal[400005];
int dep[400005], lg[400005];
int f[400005][35];
struct edge
{
    int u;
    int v;
    int w;
} e[200005];
struct node
{
    int v;
    int nxt;
} a[400005];
struct tree
{
    int l;
    int r;
    int id;
    int num;
} tr[10000005];
bool cmp(edge aa, edge bb)
{
    return aa.w < bb.w;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void add(int &x, int l, int r, int w)
{
    x = ++num;
    if (l == r)
    {
        tr[x].num = 1;
        tr[x].id = l;
        return;
    }
    int mid = (l + r) >> 1;
    if (w <= mid)
    {
        add(tr[x].l, l, mid, w);
        tr[x].num = tr[tr[x].l].num;
        tr[x].id = tr[tr[x].l].id;
    }
    else
    {
        add(tr[x].r, mid + 1, r, w);
        tr[x].num = tr[tr[x].r].num;
        tr[x].id = tr[tr[x].r].id;
    }
    return;
}
int merge(int x, int y, int l, int r)
{
    if (!x || !y)
        return x | y;
    if (l == r)
    {
        tr[x].num = tr[x].num + tr[y].num;
        return x;
    }
    int mid = (l + r) >> 1;
    tr[x].l = merge(tr[x].l, tr[y].l, l, mid);
    tr[x].r = merge(tr[x].r, tr[y].r, mid + 1, r);
    if (tr[tr[x].l].num >= tr[tr[x].r].num)
    {
        tr[x].id = tr[tr[x].l].id;
        tr[x].num = tr[tr[x].l].num;
    }
    else
    {
        tr[x].id = tr[tr[x].r].id;
        tr[x].num = tr[tr[x].r].num;
    }
    return x;
}
void dfs(int k, int ff)
{
    f[k][0] = ff;
    for (int i = 1; i <= lg[dep[k]]; ++i)
        f[k][i] = f[f[k][i - 1]][i - 1];
    if (!head[k])
    {
        add(rt[k], 1, n, c[k]);
        cal[k] = c[k];
        return;
    }
    int d = head[k];
    while (d)
    {
        dep[a[d].v] = dep[k] + 1;
        dfs(a[d].v, k);
        rt[k] = merge(rt[k], rt[a[d].v], 1, n);
        d = a[d].nxt;
    }
    cal[k] = tr[rt[k]].id;
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &type);
    cnt = n;
    for (int i = 1; i <= n + m; ++i)
        fa[i] = i;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        int u = getfather(e[i].u), v = getfather(e[i].v);
        if (u != v)
        {
            ++cnt;
            val[cnt] = e[i].w;
            fa[u] = cnt;
            fa[v] = cnt;
            ins(cnt, u);
            ins(cnt, v);
        }
    }
    for (int i = 2; i <= cnt; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= cnt; ++i)
        if (getfather(i) == i)
            dfs(i, 0);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (type == 2)
        {
            a = a ^ ans;
            b = b ^ ans;
        }
        int d = a;
        for (int i = lg[dep[a]]; i >= 0; --i)
            if (f[d][i] && val[f[d][i]] <= b)
                d = f[d][i];
        ans = cal[d];
        printf("%d\n", ans);
    }
    return 0;
}