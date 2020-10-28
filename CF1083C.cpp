#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
#define pii pair<int, int>
#define mp make_pair
int n, q, sum, cnt;
int val[200005], pos[200005];
int head[200005], dep[200005];
int dfn[200005], num[400005];
int lg[400005], st[400005][25];
struct node
{
    int v;
    int nxt;
} a[200005];
struct tree
{
    int l;
    int r;
    pii w;
} tr[800005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    ++cnt;
    dfn[k] = cnt;
    num[cnt] = k;
    int d = head[k];
    while (d)
    {
        dep[a[d].v] = dep[k] + 1;
        dfs(a[d].v);
        num[++cnt] = k;
        d = a[d].nxt;
    }
    return;
}
int lca(int u, int v)
{
    if (dfn[u] > dfn[v])
        swap(u, v);
    int log = lg[dfn[v] - dfn[u] + 1];
    if (dep[st[dfn[u]][log]] < dep[st[dfn[v] - (1 << log) + 1][log]])
        return st[dfn[u]][log];
    else
        return st[dfn[v] - (1 << log) + 1][log];
}
pii merge(pii x, pii y)
{
    if (!x.first || !y.first)
        return mp(x.first | y.first, x.second | y.second);
    if (x.first == -1 || y.first == -1)
        return mp(-1, -1);
    int z;
    z = lca(x.first, x.second);
    if ((lca(x.first, y.first) == y.first || lca(x.second, y.first) == y.first) && lca(z, y.first) == z)
        if ((lca(x.first, y.second) == y.second || lca(x.second, y.second) == y.second) && lca(z, y.second) == z)
            return mp(x.first, x.second);
    z = lca(x.first, y.first);
    if ((lca(x.first, x.second) == x.second || lca(y.first, x.second) == x.second) && lca(z, x.second) == z)
        if ((lca(x.first, y.second) == y.second || lca(y.first, y.second) == y.second) && lca(z, y.second) == z)
            return mp(x.first, y.first);
    z = lca(x.first, y.second);
    if ((lca(x.first, x.second) == x.second || lca(y.second, x.second) == x.second) && lca(z, x.second) == z)
        if ((lca(x.first, y.first) == y.first || lca(y.second, y.first) == y.first) && lca(z, y.first) == z)
            return mp(x.first, y.second);
    z = lca(x.second, y.first);
    if ((lca(x.second, x.first) == x.first || lca(y.first, x.first) == x.first) && lca(z, x.first) == z)
        if ((lca(x.second, y.second) == y.second || lca(y.first, y.second) == y.second) && lca(z, y.second) == z)
            return mp(x.second, y.first);
    z = lca(x.second, y.second);
    if ((lca(x.second, x.first) == x.first || lca(y.second, x.first) == x.first) && lca(z, x.first) == z)
        if ((lca(x.second, y.first) == y.first || lca(y.second, y.first) == y.first) && lca(z, y.first) == z)
            return mp(x.second, y.second);
    z = lca(y.first, y.second);
    if ((lca(y.first, x.first) == x.first || lca(y.second, x.first) == x.first) && lca(z, x.first) == z)
        if ((lca(y.first, x.second) == x.second || lca(y.second, x.second) == x.second) && lca(z, x.second) == z)
            return mp(y.first, y.second);
    return mp(-1, -1);
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].w = mp(pos[l], pos[r]);
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].w = merge(tr[lch].w, tr[rch].w);
    return;
}
void change(int id, int w)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].w = mp(pos[w], pos[w]);
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        change(lch, w);
    else
        change(rch, w);
    tr[id].w = merge(tr[lch].w, tr[rch].w);
    return;
}
int query(int id, pii w)
{
    if (tr[id].l == tr[id].r)
        return tr[id].l;
    pii now = merge(w, tr[lch].w);
    if (now.first == -1)
        return query(lch, w);
    else
        return query(rch, now);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &val[i]);
        pos[val[i]] = i;
    }
    for (int i = 2; i <= n; ++i)
    {
        int p;
        scanf("%d", &p);
        ins(p, i);
    }
    dfs(1);
    for (int i = 2; i <= cnt; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= cnt; ++i)
        st[i][0] = num[i];
    for (int i = 1; i <= lg[cnt]; ++i)
        for (int j = 1; j <= cnt - (1 << i) + 1; ++j)
            if (dep[st[j][i - 1]] < dep[st[j + (1 << (i - 1))][i - 1]])
                st[j][i] = st[j][i - 1];
            else
                st[j][i] = st[j + (1 << (i - 1))][i - 1];
    build(1, 0, n - 1);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            swap(val[x], val[y]);
            swap(pos[val[x]], pos[val[y]]);
            change(1, val[x]);
            change(1, val[y]);
        }
        else
        {
            if (tr[1].w.first != -1)
                printf("%d\n", n);
            else
                printf("%d\n", query(1, mp(0, 0)));
        }
    }
    return 0;
}