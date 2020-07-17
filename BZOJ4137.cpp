#include <iostream>
#include <cstdio>
#include <vector>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, t, cnt, a[100005], rt[100005];
struct trie
{
    int l;
    int r;
    int sum;
} tri[100005 * 200];
struct tree
{
    int l;
    int r;
    vector<int> id;
    vector<int> tim;
} tr[400005];
void ins(int y, int &x, int t, int val)
{
    x = ++cnt;
    tri[x] = tri[y];
    ++tri[x].sum;
    if (t == -1)
        return;
    if ((val & (1 << t)) == 0)
        ins(tri[y].l, tri[x].l, t - 1, val);
    else
        ins(tri[y].r, tri[x].r, t - 1, val);
    return;
}
int ask(int x, int y, int t, int val)
{
    if (t == -1)
        return 0;
    if ((val & (1 << t)) == 0)
    {
        if (tri[tri[y].r].sum - tri[tri[x].r].sum > 0)
            return (1 << t) + ask(tri[x].r, tri[y].r, t - 1, val);
        else
            return ask(tri[x].l, tri[y].l, t - 1, val);
    }
    else
    {
        if (tri[tri[y].l].sum - tri[tri[x].l].sum > 0)
            return (1 << t) + ask(tri[x].l, tri[y].l, t - 1, val);
        else
            return ask(tri[x].r, tri[y].r, t - 1, val);
    }
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].id.push_back(0);
    tr[id].tim.push_back(0);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
void change(int id, int pos, int val)
{
    int new_rt;
    ins(tr[id].id.back(), new_rt, 16, val);
    tr[id].id.push_back(new_rt);
    tr[id].tim.push_back(t);
    if (tr[id].l == tr[id].r)
        return;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (pos <= mid)
        change(lch, pos, val);
    else
        change(rch, pos, val);
    return;
}
int query(int id, int l, int r, int x, int d)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        if (tr[id].id.size() <= 1 || tr[id].tim.back() + d <= t)
            return 0;
        int lef = 1, rig = tr[id].id.size() - 1;
        while (lef < rig)
        {
            int mid = (lef + rig) >> 1;
            if (tr[id].tim[mid] + d <= t)
                lef = mid + 1;
            else
                rig = mid;
        }
        return ask(tr[id].id[lef - 1], tr[id].id.back(), 16, x);
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r, x, d);
    if (l >= mid + 1)
        return query(rch, l, r, x, d);
    if (l <= mid && r >= mid + 1)
        return max(query(lch, l, mid, x, d), query(rch, mid + 1, r, x, d));
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        ins(rt[i - 1], rt[i], 16, a[i]);
    }
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 0)
            ++t;
        if (type == 0)
        {
            int s, v;
            scanf("%d%d", &s, &v);
            change(1, s, v);
        }
        else
        {
            int l, r, x, d;
            scanf("%d%d%d%d", &l, &r, &x, &d);
            int ans = max(query(1, l, r, x, d), ask(rt[l - 1], rt[r], 16, x));
            printf("%d\n", ans);
        }
    }
    return 0;
}