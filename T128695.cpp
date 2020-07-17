#include <iostream>
#include <cstdio>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
typedef long long ll;
int n, q, sum, cnt;
int siz[100005], w[100005], son[100005];
int head[100005], dep[100005], fa[100005];
int top[100005], dfn[100005], num[100005];
struct node
{
    int v;
    int nxt;
} a[200005];
struct tree
{
    int l;
    int r;
    int siz;
    ll num;
    ll cnt;
    ll num_son;
    ll lazy;
} tr[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k, int f)
{
    fa[k] = f;
    siz[k] = 1;
    dep[k] = dep[f] + 1;
    son[k] = -1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int topf)
{
    ++cnt;
    dfn[k] = cnt;
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
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].num = w[num[l]];
        int d = head[num[l]];
        while (d)
        {
            if (a[d].v != fa[num[l]])
            {
                tr[id].num_son += w[a[d].v];
                ++tr[id].siz;
            }
            d = a[d].nxt;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].siz = tr[lch].siz + tr[rch].siz;
    tr[id].num_son = tr[lch].num_son + tr[rch].num_son;
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        ll lazy = tr[id].lazy;
        tr[id].lazy = 0;
        tr[lch].cnt += lazy;
        tr[rch].cnt += lazy;
        tr[lch].num_son += lazy * tr[lch].siz;
        tr[rch].num_son += lazy * tr[rch].siz;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
    }
    return;
}
void add_1(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].cnt += val;
        tr[id].num_son += (ll)val * tr[id].siz;
        tr[id].lazy += val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add_1(lch, l, r, val);
    if (l >= mid + 1)
        add_1(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        add_1(lch, l, mid, val);
        add_1(rch, mid + 1, r, val);
    }
    tr[id].num_son = tr[lch].num_son + tr[rch].num_son;
    return;
}
void add_2(int id, int w, int val)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
    {
        tr[id].num += val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add_2(lch, w, val);
    if (w >= mid + 1)
        add_2(rch, w, val);
    tr[id].num_son = tr[lch].num_son + tr[rch].num_son;
    return;
}
void add_3(int id, int w, int val)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
    {
        tr[id].num_son += val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add_3(lch, w, val);
    if (w >= mid + 1)
        add_3(rch, w, val);
    tr[id].num_son = tr[lch].num_son + tr[rch].num_son;
    return;
}
ll ask_1(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num_son;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask_1(lch, l, r);
    if (l >= mid + 1)
        return ask_1(rch, l, r);
    return ask_1(lch, l, mid) + ask_1(rch, mid + 1, r);
}
ll ask_2(int id, int w)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
        return tr[id].num;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        return ask_2(lch, w);
    if (w >= mid + 1)
        return ask_2(rch, w);
}
ll ask_3(int id, int w)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
        return tr[id].cnt;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        return ask_3(lch, w);
    if (w >= mid + 1)
        return ask_3(rch, w);
}
void change(int u, int v, int val)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        add_1(1, dfn[top[u]], dfn[u], val);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    add_1(1, dfn[u], dfn[v], val);
    add_2(1, dfn[u], val);
    u = fa[u];
    if (u)
    {
        add_2(1, dfn[u], val);
        add_3(1, dfn[u], val);
    }
    u = fa[u];
    if (u)
        add_3(1, dfn[u], val);
    return;
}
ll query(int u, int v)
{
    ll ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans += ask_1(1, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    ans += ask_1(1, dfn[u], dfn[v]) + ask_2(1, dfn[u]);
    u = fa[u];
    if (u)
        ans += ask_2(1, dfn[u]) + ask_3(1, dfn[u]);
    u = fa[u];
    if (u)
        ans += ask_3(1, dfn[u]);
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ins(x, y);
        ins(y, x);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1)
        {
            int c;
            scanf("%d", &c);
            change(x, y, c);
        }
        if (t == 2)
            printf("%lld\n", query(x, y));
    }
    return 0;
}