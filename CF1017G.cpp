#include <iostream>
#include <cstdio>
#define int long long
#define mp make_pair
#define inf 0x7fffffffffffffff
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, q, sum, cnt;
int head[100005], siz[100005], son[100005];
int top[100005], fa[100005], num[100005];
int dfn[100005], rev[100005];
struct node
{
    int v;
    int nxt;
} a[100005];
struct tree
{
    int l;
    int r;
    int num;
    int sum;
    int lazy;
} tr[400005];
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
    siz[k] = 1;
    son[k] = -1;
    int d = head[k];
    while (d)
    {
        fa[a[d].v] = k;
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
    rev[k] = cnt;
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].num = -1;
        tr[id].sum = -1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].num = max(tr[rch].num, tr[lch].num + tr[rch].sum);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r && tr[id].lazy == -1)
    {
        int lazy = tr[id].lazy;
        tr[id].lazy = 0;
        tr[lch].num = lazy;
        tr[rch].num = lazy;
        tr[lch].sum = lazy * (tr[lch].r - tr[lch].l + 1);
        tr[rch].sum = lazy * (tr[rch].r - tr[rch].l + 1);
        tr[lch].lazy = lazy;
        tr[rch].lazy = lazy;
    }
    return;
}
void add(int id, int w)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
    {
        ++tr[id].num;
        ++tr[id].sum;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w);
    else
        add(rch, w);
    tr[id].num = max(tr[rch].num, tr[lch].num + tr[rch].sum);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
void change(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num = val;
        tr[id].sum = val * (r - l + 1);
        tr[id].lazy = val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        change(lch, l, r, val);
    if (l >= mid + 1)
        change(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        change(lch, l, mid, val);
        change(rch, mid + 1, r, val);
    }
    tr[id].num = max(tr[rch].num, tr[lch].num + tr[rch].sum);
    tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
pair<int, int> ask(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return mp(tr[id].num, tr[id].sum);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    if (l <= mid && r >= mid + 1)
    {
        pair<int, int> L = ask(lch, l, mid);
        pair<int, int> R = ask(rch, mid + 1, r);
        return mp(max(L.first + R.second, R.first), L.second + R.second);
    }
}
int query(int k)
{
    int num = -inf, sum = 0;
    while (k)
    {
        pair<int, int> tmp = ask(1, dfn[top[k]], dfn[k]);
        num = max(num, tmp.first + sum);
        sum += tmp.second;
        k = fa[top[k]];
    }
    return num;
}
signed main()
{
    scanf("%lld%lld", &n, &q);
    for (int i = 2; i <= n; ++i)
    {
        int p;
        scanf("%lld", &p);
        ins(p, i);
    }
    dfs1(1);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= q; ++i)
    {
        int type, x;
        scanf("%lld%lld", &type, &x);
        if (type == 1)
            add(1, dfn[x]);
        if (type == 2)
        {
            change(1, dfn[x], rev[x], -1);
            if (fa[x])
            {
                int tmp = query(fa[x]);
                if (tmp < 0)
                    tmp = 0;
                change(1, dfn[x], dfn[x], -tmp - 1);
            }
            else
                change(1, dfn[x], dfn[x], -1);
        }
        if (type == 3)
        {
            if (query(x) >= 0)
                puts("black");
            else
                puts("white");
        }
    }
    return 0;
}