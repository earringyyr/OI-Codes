#include <iostream>
#include <cstdio>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, sum, cnt;
int u[100005], v[100005], w[100005], head[100005];
int dfn[100005], top[100005], dep[100005], son[100005];
int siz[100005], num[100005], fa[100005], ww[100005];
struct node
{
    int v;
    int w;
    int nxt;
} a[200005];
struct tree
{
    int l;
    int r;
    int max;
    int lazy_sum;
    int lazy_change;
} tr[400005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int f, int id)
{
    fa[id] = f;
    siz[id] = 1;
    son[id] = -1;
    dep[id] = dep[f] + 1;
    int d = head[id];
    while (d)
    {
        if (a[d].v != f)
        {
            dfs1(id, a[d].v);
            siz[id] += siz[a[d].v];
            ww[a[d].v] = a[d].w;
            if (son[id] == -1 || siz[son[id]] < siz[a[d].v])
                son[id] = a[d].v;
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int topf, int id)
{
    ++cnt;
    dfn[id] = cnt;
    num[cnt] = id;
    top[id] = topf;
    if (son[id] != -1)
        dfs2(topf, son[id]);
    int d = head[id];
    while (d)
    {
        if (a[d].v != fa[id] && a[d].v != son[id])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].lazy_change = -1;
    if (l == r)
    {
        tr[id].max = ww[num[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].max = max(tr[lch].max, tr[rch].max);
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r)
    {
        if (tr[id].lazy_change != -1)
        {
            tr[lch].lazy_sum = 0;
            tr[rch].lazy_sum = 0;
            tr[lch].lazy_change = tr[id].lazy_change;
            tr[rch].lazy_change = tr[id].lazy_change;
            tr[lch].max = tr[id].lazy_change;
            tr[rch].max = tr[id].lazy_change;
        }
        tr[lch].lazy_sum += tr[id].lazy_sum;
        tr[rch].lazy_sum += tr[id].lazy_sum;
        tr[lch].max += tr[id].lazy_sum;
        tr[rch].max += tr[id].lazy_sum;
        tr[id].lazy_change = -1;
        tr[id].lazy_sum = 0;
    }
    return;
}
void change(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].max = val;
        tr[id].lazy_change = val;
        tr[id].lazy_sum = 0;
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
    tr[id].max = max(tr[lch].max, tr[rch].max);
    return;
}
void add(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].max += val;
        tr[id].lazy_sum += val;
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
    tr[id].max = max(tr[lch].max, tr[rch].max);
    return;
}
int ask(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].max;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    return max(ask(lch, l, mid), ask(rch, mid + 1, r));
}
void change_lian(int u, int v, int w)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        change(1, dfn[top[u]], dfn[u], w);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    if (dfn[u] != dfn[v])
        change(1, dfn[u] + 1, dfn[v], w);
    return;
}
void add_lian(int u, int v, int w)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        add(1, dfn[top[u]], dfn[u], w);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    if (dfn[u] != dfn[v])
        add(1, dfn[u] + 1, dfn[v], w);
    return;
}
int ask_lian(int u, int v)
{
    int ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans = max(ans, ask(1, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    if (dfn[u] != dfn[v])
        ans = max(ans, ask(1, dfn[u] + 1, dfn[v]));
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
        ins(u[i], v[i], w[i]);
        ins(v[i], u[i], w[i]);
    }
    dfs1(0, 1);
    dfs2(1, 1);
    build(1, 1, n);
    string type;
    while (cin >> type)
    {
        if (type == "Stop")
            break;
        else if (type == "Change")
        {
            int k, w;
            scanf("%d%d", &k, &w);
            change_lian(u[k], v[k], w);
        }
        else if (type == "Cover")
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            change_lian(u, v, w);
        }
        else if (type == "Add")
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_lian(u, v, w);
        }
        else if (type == "Max")
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", ask_lian(u, v));
        }
    }
    return 0;
}