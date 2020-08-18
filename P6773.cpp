#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, sum, cnt, num, ans, head[500005];
int x[500005], y[500005];
int fa[500005], son[500005], siz[500005];
int dep[500005], top[500005], dfn[500005];
struct node
{
    int v;
    int nxt;
} a[1000005];
struct tree
{
    int l;
    int r;
    int num;
    int lazy;
} tr[2000005];
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
    siz[k] = 1;
    fa[k] = f;
    son[k] = -1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dep[a[d].v] = dep[k] + 1;
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
int lowbit(int x)
{
    return x & -x;
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
    if (tr[id].lazy && tr[id].l != tr[id].r)
    {
        if (tr[id].lazy == -1)
        {
            tr[id].lazy = 0;
            tr[lch].num = 0;
            tr[rch].num = 0;
            tr[lch].lazy = -1;
            tr[rch].lazy = -1;
        }
        else
        {
            tr[id].lazy = 0;
            tr[lch].num = tr[lch].r - tr[lch].l + 1;
            tr[rch].num = tr[rch].r - tr[rch].l + 1;
            tr[lch].lazy = 1;
            tr[rch].lazy = 1;
        }
    }
    return;
}
void add(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num = r - l + 1;
        tr[id].lazy = 1;
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
    tr[id].num = tr[lch].num + tr[rch].num;
    return;
}
void calc(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        add(1, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    if (dfn[u] != dfn[v])
        add(1, dfn[u] + 1, dfn[v]);
    return;
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
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &x[i], &y[i]);
    for (int i = 1; i < (1 << m); ++i)
    {
        num = 0;
        for (int j = 0; j < m; ++j)
            if (i & (1 << j))
            {
                ++num;
                calc(x[j + 1], y[j + 1]);
            }
        ans = (ans + ksm(-1, num - 1) * ksm(2, n - tr[1].num - 1) + mod) % mod;
        tr[1].num = 0;
        tr[1].lazy = -1;
    }
    ans = (ksm(2, n - 1) - ans + mod) % mod;
    printf("%d", ans);
    return 0;
}