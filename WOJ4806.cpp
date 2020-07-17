#include <iostream>
#include <cstdio>
#include <cmath>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int t, n, k, a[200005];
struct node
{
    int l;
    int r;
    int mi;
    int ma;
} tr[800005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].ma = a[l];
        tr[id].mi = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].ma = max(tr[lch].ma, tr[rch].ma);
    tr[id].mi = min(tr[lch].mi, tr[rch].mi);
    return;
}
int query_ma(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].ma;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query_ma(lch, l, r);
    if (l >= mid + 1)
        return query_ma(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return max(query_ma(lch, l, mid), query_ma(rch, mid + 1, r));
}
int query_mi(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].mi;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query_mi(lch, l, r);
    if (l >= mid + 1)
        return query_mi(rch, l, r);
    if (l <= mid && r >= mid + 1)
        return min(query_mi(lch, l, mid), query_mi(rch, mid + 1, r));
}
bool dfs(int l, int r)
{
    if (l >= r)
        return true;
    int maxn = query_ma(1, l, r), minn = query_mi(1, l, r);
    int head = l, tail = r, pos = -1;
    while (head <= tail)
    {
        if (abs(a[head] - maxn) <= k && abs(a[head] - minn) <= k)
        {
            pos = head;
            break;
        }
        if (abs(a[tail] - maxn) <= k && abs(a[tail] - minn) <= k)
        {
            pos = tail;
            break;
        }
        ++head;
        --tail;
    }
    if (pos == -1)
        return false;
    if (dfs(l, pos - 1) && dfs(pos + 1, r))
        return true;
    return false;
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        build(1, 1, n);
        if (dfs(1, n))
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}