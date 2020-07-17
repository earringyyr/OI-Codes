#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, m, x, cnt, t[100005], num[100005], sum[100005], rt[100005];
struct tree
{
    int l;
    int r;
    int sum;
} tr[7500005];
void add(int y, int &x, int l, int r, int w)
{
    x = ++cnt;
    tr[x] = tr[y];
    ++tr[x].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (w <= mid)
        add(tr[y].l, tr[x].l, l, mid, w);
    else
        add(tr[y].r, tr[x].r, mid + 1, r, w);
    return;
}
int query(int id, int l, int r, int ql, int qr)
{
    if (!id)
        return 0;
    if (ql == l && qr == r)
        return tr[id].sum;
    int mid = (l + r) >> 1;
    if (qr <= mid)
        return query(tr[id].l, l, mid, ql, qr);
    if (ql >= mid + 1)
        return query(tr[id].r, mid + 1, r, ql, qr);
    if (ql <= mid && qr >= mid + 1)
        return query(tr[id].l, l, mid, ql, mid) + query(tr[id].r, mid + 1, r, mid + 1, qr);
}
int check(int k)
{
    int res = 0;
    int pos = lower_bound(t + 1, t + n + 1, k) - t;
    res = sum[pos] - (k / x) * (n - pos + 1);
    res += query(rt[pos], 0, x, k % x + 1, x);
    return res;
}
int solve(int s)
{
    int l = 0, r = t[n], ans = 0;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid) > s)
            l = mid + 1;
        else
            r = mid;
    }
    ans = l;
    return max(ans - s, 0LL);
}
signed main()
{
    scanf("%lld%lld%lld", &n, &m, &x);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &t[i]);
    sort(t + 1, t + n + 1);
    for (int i = 1; i <= n; ++i)
        num[i] = t[i] / x;
    for (int i = n; i >= 1; --i)
    {
        sum[i] = sum[i + 1] + num[i];
        rt[i] = rt[i + 1];
        add(rt[i + 1], rt[i], 0, x, t[i] % x);
    }
    for (int i = 1; i <= m; ++i)
    {
        int s;
        scanf("%lld", &s);
        printf("%lld\n", solve(s));
    }
    return 0;
}