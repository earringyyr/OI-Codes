#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
typedef long long ll;
int n, t[1000005];
ll val[1000005];
struct node
{
    int pos;
    int tim;
    node(int aa, int bb)
    {
        pos = aa;
        tim = bb;
    }
    bool operator<(const node &bb) const
    {
        return tim > bb.tim;
    }
};
priority_queue<node> q;
struct tree
{
    int l;
    int r;
    ll val;
} tr[4000005];
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
void add(int id, int w, ll val)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].val = val;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w, val);
    else
        add(rch, w, val);
    tr[id].val = max(tr[lch].val, tr[rch].val);
    return;
}
ll query(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].val;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    return max(query(lch, l, mid), query(rch, mid + 1, r));
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &t[i]);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &val[i]);
        val[i] *= t[i];
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        while (!q.empty() && i >= q.top().tim)
        {
            add(1, q.top().pos, val[q.top().pos]);
            q.pop();
        }
        if (i - t[i] > 0)
            val[i] += query(1, 1, i - t[i]);
        q.push(node(i, i + t[i]));
    }
    while (!q.empty())
    {
        add(1, q.top().pos, val[q.top().pos]);
        q.pop();
    }
    printf("%lld", query(1, 1, n));
    return 0;
}