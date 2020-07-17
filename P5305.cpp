#include <iostream>
#include <cstdio>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
#define mod 998244353
using namespace std;
typedef long long ll;
int n, Q, k, sum, cnt;
int head[50005], dep[50005], son[50005], num[50005], fa[50005];
int top[50005], dfn[50005], siz[50005], pw[50005], ans[50005];
struct node
{
    int v;
    int nxt;
} a[50005];
struct point
{
    int id;
    int x;
    int y;
} q[50005];
struct tree
{
    int l;
    int r;
    int num;
    int lazy;
} tr[200005];
bool cmp(point aa, point bb)
{
    return aa.x < bb.x;
}
int ksm(int a, int k)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (ll)b * a % mod;
        a = (ll)a * a % mod;
        k >>= 1;
    }
    return b;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k)
{
    son[k] = -1;
    siz[k] = 1;
    dep[k] = dep[fa[k]] + 1;
    int d = head[k];
    while (d)
    {
        dfs1(a[d].v);
        siz[k] += siz[a[d].v];
        if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
            son[k] = a[d].v;
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
        if (a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
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
        tr[id].lazy = 0;
        tr[lch].lazy += lazy;
        tr[rch].lazy += lazy;
        tr[lch].num = (tr[lch].num + (ll)(pw[dep[num[tr[lch].r]]] - pw[dep[num[tr[lch].l]] - 1]) * lazy % mod) % mod;
        tr[rch].num = (tr[rch].num + (ll)(pw[dep[num[tr[rch].r]]] - pw[dep[num[tr[rch].l]] - 1]) * lazy % mod) % mod;
    }
    return;
}
void add(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        ++tr[id].lazy;
        tr[id].num = (tr[id].num + pw[dep[num[tr[id].r]]] - pw[dep[num[tr[id].l]] - 1]) % mod;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r);
    if (l >= mid + 1)
        add(rch, l, r);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid);
        add(rch, mid + 1, r);
    }
    tr[id].num = (tr[lch].num + tr[rch].num) % mod;
    return;
}
int ask(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    return (ask(lch, l, mid) + ask(rch, mid + 1, r)) % mod;
}
void change(int u)
{
    while (top[u])
    {
        add(1, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    return;
}
int query(int u)
{
    int ans = 0;
    while (top[u])
    {
        ans = (ans + ask(1, dfn[top[u]], dfn[u])) % mod;
        u = fa[top[u]];
    }
    return ans;
}
int main()
{
    scanf("%d%d%d", &n, &Q, &k);
    for (int i = 1; i <= n; ++i)
        pw[i] = ksm(i, k);
    for (int i = 2; i <= n; ++i)
    {
        scanf("%d", &fa[i]);
        ins(fa[i], i);
    }
    dfs1(1);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= Q; ++i)
    {
        q[i].id = i;
        scanf("%d%d", &q[i].x, &q[i].y);
    }
    sort(q + 1, q + Q + 1, cmp);
    int w = 0;
    for (int i = 1; i <= Q; ++i)
    {
        while (w < q[i].x)
            change(++w);
        ans[q[i].id] = query(q[i].y);
    }
    for (int i = 1; i <= Q; ++i)
        printf("%d\n", (ans[i] + mod) % mod);
    return 0;
}