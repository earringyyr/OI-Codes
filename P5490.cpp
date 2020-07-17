#include <iostream>
#include <cstdio>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
#define int long long
using namespace std;
struct node
{
    int x;
    int y1;
    int y2;
    int flag;
} a[200005];
struct tree
{
    int l;
    int r;
    int sum;
    int lazy;
} tr[1600005];
int n, m, len, ans, b[200005];
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
void update(int id, int l, int r, int flag)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].lazy += flag;
        if (tr[id].lazy > 0)
            tr[id].sum = b[r + 1] - b[l];
        else
            tr[id].sum = tr[lch].sum + tr[rch].sum;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        update(lch, l, r, flag);
    if (l >= mid + 1)
        update(rch, l, r, flag);
    if (l <= mid && r >= mid + 1)
    {
        update(lch, l, mid, flag);
        update(rch, mid + 1, r, flag);
    }
    if (tr[id].lazy > 0)
        tr[id].sum = b[tr[id].r + 1] - b[tr[id].l];
    else
        tr[id].sum = tr[lch].sum + tr[rch].sum;
    return;
}
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
signed main()
{
    scanf("%lld", &n);
    m = 2 * n;
    for (int i = 1; i <= n; ++i)
    {
        int x1, x2, y1, y2;
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        a[i].x = x1;
        a[i].y1 = y1;
        a[i].y2 = y2;
        a[i].flag = 1;
        a[i + n].x = x2;
        a[i + n].y1 = y1;
        a[i + n].y2 = y2;
        a[i + n].flag = -1;
        b[i] = y1;
        b[i + n] = y2;
    }
    sort(a + 1, a + m + 1, cmp);
    sort(b + 1, b + m + 1);
    len = unique(b + 1, b + m + 1) - b - 1;
    for (int i = 1; i <= m; ++i)
    {
        a[i].y1 = lower_bound(b + 1, b + len + 1, a[i].y1) - b;
        a[i].y2 = lower_bound(b + 1, b + len + 1, a[i].y2) - b;
    }
    build(1, 1, len - 1);
    update(1, a[1].y1, a[1].y2 - 1, a[1].flag);
    for (int i = 2; i <= m; ++i)
    {
        ans += (a[i].x - a[i - 1].x) * tr[1].sum;
        update(1, a[i].y1, a[i].y2 - 1, a[i].flag);
    }
    printf("%lld", ans);
    return 0;
}