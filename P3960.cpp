#include <iostream>
#include <cstdio>
#include <vector>
#define int long long
using namespace std;
int n, m, q, cnt, len, rt[300005];
vector<int> f[300005];
struct node
{
    int l;
    int r;
    int sum;
} tr[300005 * 20 * 4];
int query(int &id, int l, int r, int val)
{
    if (!id)
        id = ++cnt;
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (mid - l + 1 - tr[tr[id].l].sum >= val)
        return query(tr[id].l, l, mid, val);
    else
        return query(tr[id].r, mid + 1, r, val - mid + l - 1 + tr[tr[id].l].sum);
}
void add(int &id, int l, int r, int w)
{
    if (!id)
        id = ++cnt;
    ++tr[id].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[id].l, l, mid, w);
    if (w >= mid + 1)
        add(tr[id].r, mid + 1, r, w);
    return;
}
int query1(int x, int id)
{
    int pos = query(rt[n + 1], 1, len, x);
    add(rt[n + 1], 1, len, pos);
    if (pos <= n)
        pos = pos * m;
    else
        pos = f[n + 1][pos - n - 1];
    if (id)
        f[n + 1].push_back(id);
    else
        f[n + 1].push_back(pos);
    return pos;
}
int query2(int x, int y)
{
    int pos = query(rt[x], 1, len, y);
    add(rt[x], 1, len, pos);
    if (pos < m)
        pos = (x - 1) * m + pos;
    else
        pos = f[x][pos - m];
    f[x].push_back(query1(x, pos));
    return pos;
}
signed main()
{
    scanf("%lld%lld%lld", &n, &m, &q);
    len = n + m + q;
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        scanf("%lld%lld", &x, &y);
        if (y == m)
            printf("%lld\n", query1(x, 0));
        else
            printf("%lld\n", query2(x, y));
    }
    return 0;
}