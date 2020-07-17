#include <iostream>
#include <cstdio>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, m, sum;
int c[100005];
int head[100005], fa[100005];
int top[100005], dep[100005];
int dfn[100005], b[100005];
int son[100005], siz[100005];
struct node
{
    int v;
    int next;
} a[200005];
struct tree
{
    int l;
    int r;
    int cl;
    int cr;
    int num;
    int lazy;
} tr[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void pushdown(int id)
{
    if (tr[id].l != tr[id].r && tr[id].lazy != 0)
    {
        tr[lch].cl = tr[lch].cr = tr[id].lazy;
        tr[rch].cl = tr[rch].cr = tr[id].lazy;
        tr[lch].num = tr[rch].num = 1;
        tr[lch].lazy = tr[rch].lazy = tr[id].lazy;
        tr[id].lazy = 0;
    }
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].num = 1;
        tr[id].cl = tr[id].cr = c[b[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].cl = tr[lch].cl;
    tr[id].cr = tr[rch].cr;
    tr[id].num = tr[lch].cr == tr[rch].cl ? tr[lch].num + tr[rch].num - 1 : tr[lch].num + tr[rch].num;
    return;
}
void gai(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num = 1;
        tr[id].cl = tr[id].cr = val;
        tr[id].lazy = val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (mid >= r)
        gai(lch, l, r, val);
    if (mid + 1 <= l)
        gai(rch, l, r, val);
    if (mid >= l && mid + 1 <= r)
    {
        gai(lch, l, mid, val);
        gai(rch, mid + 1, r, val);
    }
    tr[id].cl = tr[lch].cl;
    tr[id].cr = tr[rch].cr;
    tr[id].num = tr[lch].cr == tr[rch].cl ? tr[lch].num + tr[rch].num - 1 : tr[lch].num + tr[rch].num;
    return;
}
int wen(int id, int l, int r)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (mid >= r)
        return wen(lch, l, r);
    if (mid + 1 <= l)
        return wen(rch, l, r);
    if (mid >= l && mid + 1 <= r)
    {
        return tr[lch].cr == tr[rch].cl ? wen(lch, l, mid) + wen(rch, mid + 1, r) - 1 : wen(lch, l, mid) + wen(rch, mid + 1, r);
    }
}
int wenn(int id, int k)
{
    pushdown(id);
    if (tr[id].l == k && tr[id].r == k)
        return tr[id].cl;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (mid >= k)
        return wenn(lch, k);
    if (mid + 1 <= k)
        return wenn(rch, k);
}
void dfs1(int id, int f, int deep)
{
    fa[id] = f;
    dep[id] = deep;
    siz[id] = 1;
    son[id] = -1;
    int d = head[id];
    while (d)
    {
        if (a[d].v != fa[id])
        {
            dfs1(a[d].v, id, deep + 1);
            siz[id] += siz[a[d].v];
            if (son[id] == -1 || siz[son[id]] < siz[a[d].v])
                son[id] = a[d].v;
        }
        d = a[d].next;
    }
    return;
}
void dfs2(int id, int topf)
{
    ++sum;
    dfn[id] = sum;
    b[sum] = id;
    top[id] = topf;
    if (son[id] != -1)
        dfs2(son[id], topf);
    int d = head[id];
    while (d)
    {
        if (a[d].v != fa[id] && a[d].v != son[id])
            dfs2(a[d].v, a[d].v);
        d = a[d].next;
    }
    return;
}
void change(int u, int v, int val)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        gai(1, dfn[top[u]], dfn[u], val);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    gai(1, dfn[u], dfn[v], val);
    return;
}
int ask(int u, int v)
{
    int ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans += wen(1, dfn[top[u]], dfn[u]);
        if (wenn(1, dfn[fa[top[u]]]) == wenn(1, dfn[top[u]]))
            ans--;
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    ans += wen(1, dfn[u], dfn[v]);
    return ans;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        ins(x, y);
        ins(y, x);
    }
    sum = 0;
    dfs1(1, 0, 1);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        char pan;
        cin >> pan;
        if (pan == 'C')
        {
            int aa, bb, cc;
            cin >> aa >> bb >> cc;
            change(aa, bb, cc);
        }
        else
        {
            int aa, bb;
            cin >> aa >> bb;
            cout << ask(aa, bb) << endl;
        }
    }
    return 0;
}