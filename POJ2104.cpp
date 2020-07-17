#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, len, cnt, a[200005], b[200005], rt[200005];
struct tree
{
    int l;
    int r;
    int sum;
} tr[200000 * 18];
int query(int x, int y, int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (tr[tr[x].l].sum - tr[tr[y].l].sum >= k)
        return query(tr[x].l, tr[y].l, l, mid, k);
    else
        return query(tr[x].r, tr[y].r, mid + 1, r, k - (tr[tr[x].l].sum - tr[tr[y].l].sum));
}
void build(int y, int &x, int l, int r, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    ++tr[x].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (val <= mid)
        build(tr[y].l, tr[x].l, l, mid, val);
    else
        build(tr[y].r, tr[x].r, mid + 1, r, val);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
    {
        a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
        build(rt[i - 1], rt[i], 1, len, a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", b[query(rt[r], rt[l - 1], 1, len, k)]);
    }
    return 0;
}