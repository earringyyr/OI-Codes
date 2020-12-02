#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, cnt, rt, sum, top, col, num;
int head[500005], st[500005];
int dfn[500005], low[500005], co[500005];
struct node
{
    int id;
    int iid;
    int pos;
} w[20005];
struct tree
{
    int l;
    int r;
    int L;
    int R;
} tr[400005];
struct edge
{
    int v;
    int nxt;
} a[1000005];
bool cmp(node aa, node bb)
{
    return aa.pos < bb.pos;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void build(int &x, int l, int r)
{
    x = ++cnt;
    if (l == r)
    {
        ins(x, w[l].iid);
        tr[x].L = w[l].pos;
        tr[x].R = w[l].pos;
        return;
    }
    int mid = (l + r) >> 1;
    build(tr[x].l, l, mid);
    build(tr[x].r, mid + 1, r);
    ins(x, tr[x].l);
    ins(x, tr[x].r);
    tr[x].L = tr[tr[x].l].L;
    tr[x].R = tr[tr[x].r].R;
    return;
}
void add(int x, int l, int r, int pos, int dis)
{
    int mid = (l + r) >> 1;
    if (pos >= l && pos <= r)
    {
        if (l == r)
            return;
        if (tr[tr[x].l].L - w[pos].pos < dis && w[pos].pos - tr[tr[x].l].R < dis)
            add(tr[x].l, l, mid, pos, dis);
        if (tr[tr[x].r].L - w[pos].pos < dis && w[pos].pos - tr[tr[x].r].R < dis)
            add(tr[x].r, mid + 1, r, pos, dis);
        return;
    }
    if (abs(tr[x].L - w[pos].pos) < dis && abs(w[pos].pos - tr[x].R) < dis)
    {
        ins(w[pos].id, x);
        return;
    }
    if (tr[tr[x].l].L - w[pos].pos < dis && w[pos].pos - tr[tr[x].l].R < dis)
        add(tr[x].l, l, mid, pos, dis);
    if (tr[tr[x].r].L - w[pos].pos < dis && w[pos].pos - tr[tr[x].r].R < dis)
        add(tr[x].r, mid + 1, r, pos, dis);
    return;
}
void tarjan(int k)
{
    ++num;
    dfn[k] = num;
    low[k] = num;
    st[++top] = k;
    int d = head[k];
    while (d != 0)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v);
            low[k] = min(low[k], low[a[d].v]);
        }
        else if (!co[a[d].v])
            low[k] = min(low[k], dfn[a[d].v]);
        d = a[d].nxt;
    }
    if (dfn[k] == low[k])
    {
        ++col;
        while (dfn[st[top]] != low[st[top]])
        {
            co[st[top]] = col;
            --top;
        }
        co[st[top]] = col;
        --top;
    }
    return;
}
bool check(int mid)
{
    sum = 0;
    num = 0;
    top = 0;
    col = 0;
    cnt = 2 * n;
    memset(head, 0, sizeof(head));
    memset(co, 0, sizeof(co));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    build(rt, 1, 2 * n);
    for (int i = 1; i <= 2 * n; ++i)
        add(rt, 1, 2 * n, i, mid);
    for (int i = 1; i <= 2 * n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (co[i] == co[i + n])
            return false;
    return true;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        w[i].id = i;
        w[i].iid = i + n;
        w[i].pos = x;
        w[i + n].id = i + n;
        w[i + n].iid = i;
        w[i + n].pos = y;
    }
    sort(w + 1, w + 2 * n + 1, cmp);
    int lef = 0, rig = 1e9;
    while (lef < rig)
    {
        int mid = (lef + rig + 1) >> 1;
        if (check(mid))
            lef = mid;
        else
            rig = mid - 1;
    }
    printf("%d", lef);
    return 0;
}