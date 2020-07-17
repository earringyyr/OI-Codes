#include <iostream>
#include <cstdio>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
#define mod 201314
using namespace std;
int n, w = -1, qq, sum, cnt, tot;
int an[50005], l[50005], r[50005];
int head[50005], fa[50005], siz[50005];
int dfn[50005], top[50005], son[50005];
struct node
{
    int v;
    int next;
} a[50005];
struct tree
{
    int l;
    int r;
    int sum;
    int lazy;
} tr[200005];
struct point
{
    int id;
    int w;
    int z;
    int type;
} q[100005];
bool cmp(point aa, point bb)
{
    return aa.w < bb.w;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k)
{
    siz[k] = 1;
    son[k] = -1;
    int d = head[k];
    while (d)
    {
        fa[a[d].v] = k;
        dfs1(a[d].v);
        if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
            son[k] = a[d].v;
        siz[k] += siz[a[d].v];
        d = a[d].next;
    }
    return;
}
void dfs2(int k, int topf)
{
    ++cnt;
    dfn[k] = cnt;
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].next;
    }
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        int lazy = tr[id].lazy;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
        tr[id].lazy = 0;
        tr[lch].sum += (long long)lazy * (tr[lch].r - tr[lch].l + 1) % mod;
        tr[rch].sum += (long long)lazy * (tr[rch].r - tr[rch].l + 1) % mod;
        tr[lch].lazy %= mod;
        tr[rch].lazy %= mod;
        tr[lch].sum %= mod;
        tr[rch].sum %= mod;
    }
    return;
}
void add(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].sum += (long long)val * (r - l + 1) % mod;
        tr[id].lazy += val;
        tr[id].sum %= mod;
        tr[id].lazy %= mod;
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
    tr[id].sum = (tr[lch].sum + tr[rch].sum) % mod;
    return;
}
int query(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].sum;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return (query(lch, l, mid) + query(rch, mid + 1, r)) % mod;
}
void add_lian(int x)
{
    while (top[x])
    {
        add(1, dfn[top[x]], dfn[x], 1);
        x = fa[top[x]];
    }
    add(1, 1, dfn[x], 1);
    return;
}
int query_lian(int x)
{
    int ans = 0;
    while (top[x])
    {
        ans += query(1, dfn[top[x]], dfn[x]);
        ans %= mod;
        x = fa[top[x]];
    }
    ans += query(1, 1, dfn[x]);
    ans %= mod;
    return ans;
}
int main()
{
    scanf("%d%d", &n, &qq);
    for (int i = 1; i < n; ++i)
    {
        int u;
        scanf("%d", &u);
        ins(u, i);
    }
    dfs1(0);
    dfs2(0, 0);
    build(1, 1, n);
    for (int i = 1; i <= qq; ++i)
    {
        int l, r, z;
        scanf("%d%d%d", &l, &r, &z);
        ++tot;
        q[tot].id = i;
        q[tot].z = z;
        q[tot].w = l - 1;
        q[tot].type = 0;
        ++tot;
        q[tot].id = i;
        q[tot].z = z;
        q[tot].w = r;
        q[tot].type = 1;
    }
    sort(q + 1, q + tot + 1, cmp);
    for (int i = 1; i <= tot; ++i)
    {
        while (q[i].w > w)
            add_lian(++w);
        if (q[i].type == 0)
            an[q[i].id] -= query_lian(q[i].z);
        else
            an[q[i].id] += query_lian(q[i].z);
        an[q[i].id] %= mod;
    }
    for (int i = 1; i <= qq; ++i)
        printf("%d\n", (an[i] + mod) % mod);
    return 0;
}