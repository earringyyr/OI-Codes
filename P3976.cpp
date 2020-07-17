#include <iostream>
#include <cstdio>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
typedef long long ll;
int n, Q, sum, cnt;
int head[50005], p[50005], fa[50005];
int dfn[50005], num[50005], top[50005];
int siz[50005], son[50005];
struct node
{
    int v;
    int nxt;
} a[100005];
struct tree
{
    int l;
    int r;
    int minx;
    int maxn;
    int f1;
    int f2;
    int lazy;
    tree(int aa = 0, int bb = 0, int cc = 0, int dd = 0, int ee = 0, int ff = 0, int gg = 0)
    {
        l = aa;
        r = bb;
        minx = cc;
        maxn = dd;
        f1 = ee;
        f2 = ff;
        lazy = gg;
    }
} tr[200005];
inline int read()
{
	char ch = getchar();
	int x = 0;
	while (!isdigit(ch))
		ch = getchar();
	while (isdigit(ch))
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x;
}
inline void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
inline void dfs1(int k, int f)
{
    fa[k] = f;
    siz[k] = 1;
    son[k] = -1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (son[k] == -1 || siz[son[k]] < siz[a[d].v])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
    return;
}
inline void dfs2(int k, int topf)
{
    dfn[k] = ++cnt;
    num[cnt] = k;
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k] && a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
    return;
}
inline void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].minx = p[num[l]];
        tr[id].maxn = p[num[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    tr[id].f1 = max(max(0, tr[rch].maxn - tr[lch].minx), max(tr[lch].f1, tr[rch].f1));
    tr[id].f2 = max(max(0, tr[lch].maxn - tr[rch].minx), max(tr[lch].f2, tr[rch].f2));
    return;
}
inline void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        ll lazy = tr[id].lazy;
        tr[id].lazy = 0;
        tr[lch].minx += lazy;
        tr[rch].minx += lazy;
        tr[lch].maxn += lazy;
        tr[rch].maxn += lazy;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
    }
    return;
}
inline void add(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].minx += val;
        tr[id].maxn += val;
        tr[id].lazy += val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r, val);
    if (l >= mid + 1)
        add(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid, val);
        add(rch, mid + 1, r, val);
    }
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    tr[id].maxn = max(tr[lch].maxn, tr[rch].maxn);
    tr[id].f1 = max(max(0, tr[rch].maxn - tr[lch].minx), max(tr[lch].f1, tr[rch].f1));
    tr[id].f2 = max(max(0, tr[lch].maxn - tr[rch].minx), max(tr[lch].f2, tr[rch].f2));
    return;
}
inline tree merge(tree x, tree y)
{
    tree z;
    z.l = x.l;
    z.r = x.r;
    z.minx = min(x.minx, y.minx);
    z.maxn = max(x.maxn, y.maxn);
    z.f1 = max(max(0, y.maxn - x.minx), max(x.f1, y.f1));
    z.f2 = max(max(0, x.maxn - y.minx), max(x.f2, y.f2));
    return z;
}
inline tree query(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id];
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return merge(query(lch, l, mid), query(rch, mid + 1, r));
}
inline int solve(int u, int v, int val)
{
    int ans = 0, type = 0, minx = 1000000005, maxn = -1000000005;
    while (top[u] != top[v])
    {
        if (dfn[fa[top[u]]] < dfn[fa[top[v]]])
        {
            swap(u, v);
            type ^= 1;
        }
        tree tmp = query(1, dfn[top[u]], dfn[u]);
        if (type == 0)
        {
            ans = max(ans, max(tmp.f2, tmp.maxn - minx));
            minx = min(minx, tmp.minx);
        }
        else
        {
            ans = max(ans, max(tmp.f1, maxn - tmp.minx));
            maxn = max(maxn, tmp.maxn);
        }
        add(1, dfn[top[u]], dfn[u], val);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    else
        type ^= 1;
    tree tmp = query(1, dfn[u], dfn[v]);
    if (type == 0)
        ans = max(ans, max(tmp.f2, max(tmp.maxn - minx, max(maxn - tmp.minx, maxn - minx))));
    else
        ans = max(ans, max(tmp.f1, max(tmp.maxn - minx, max(maxn - tmp.minx, maxn - minx))));
    add(1, dfn[u], dfn[v], val);
    return ans;
}
int main()
{
    n = read();
    for (register int i = 1; i <= n; ++i)
        p[i] = read();
    for (register int i = 1; i < n; ++i)
    {
        int x, y;
        x = read();
        y = read();
        ins(x, y);
        ins(y, x);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    Q = read();
    for (register int i = 1; i <= Q; ++i)
    {
        int A, B, v;
        A = read();
        B = read();
        v = read();
        printf("%d\n", solve(A, B, v));
    }
    return 0;
}