#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int n, m, len, cnt, sum, ans, w[100005], b[100005], lg[100005], rt[100005], dep[100005], head[100005], fa[100005][25];
struct node
{
    int v;
    int nxt;
} a[200005];
struct tree
{
    int l;
    int r;
    int num;
} tr[25 * 100005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void ins(int y, int &x, int l, int r, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    ++tr[x].num;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (val <= mid)
        ins(tr[y].l, tr[x].l, l, mid, val);
    else
        ins(tr[y].r, tr[x].r, mid + 1, r, val);
    return;
}
void dfs(int f, int k)
{
    ins(rt[f], rt[k], 1, len, w[k]);
    fa[k][0] = f;
    dep[k] = dep[f] + 1;
    for (int i = 1; i <= lg[dep[k]]; ++i)
        fa[k][i] = fa[fa[k][i - 1]][i - 1];
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
            dfs(k, a[d].v);
        d = a[d].nxt;
    }
    return;
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    while (dep[x] > dep[y])
        x = fa[x][lg[dep[x] - dep[y]]];
    if (x == y)
        return x;
    for (int i = lg[dep[x]]; i >= 0; --i)
        if (fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    return fa[x][0];
}
int query(int x, int y, int p, int q, int l, int r, int k)
{
    if (l == r)
        return b[l];
    int mid = (l + r) >> 1;
    if (tr[tr[x].l].num + tr[tr[y].l].num - tr[tr[p].l].num - tr[tr[q].l].num >= k)
        return query(tr[x].l, tr[y].l, tr[p].l, tr[q].l, l, mid, k);
    else
        return query(tr[x].r, tr[y].r, tr[p].r, tr[q].r, mid + 1, r, k - tr[tr[x].l].num - tr[tr[y].l].num + tr[tr[p].l].num + tr[tr[q].l].num);
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &w[i]);
        b[i] = w[i];
    }
    sort(b + 1, b + n + 1);
    len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
        w[i] = lower_bound(b + 1, b + len + 1, w[i]) - b;
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%lld%lld", &x, &y);
        ins(x, y);
        ins(y, x);
    }
    dfs(0, 1);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w, k;
        scanf("%lld%lld%lld", &u, &v, &k);
        w = lca(u, v);
        printf("%lld\n", ans = query(rt[u], rt[v], rt[w], rt[fa[w][0]], 1, len, k));
    }
    return 0;
}