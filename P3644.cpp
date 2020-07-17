#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int k, n, cnt, sum, tot;
int s[100005], t[100005], r[100005];
int vis[100005], rt[100005];
int d[200005], a[200005];
ll ans;
struct node
{
    int x;
    int y;
    int num;
} w[100005];
struct tree
{
    int l;
    int r;
    int num;
    ll sum;
} tr[20 * 200005];
bool cmp(node x, node y)
{
    return x.num < y.num;
}
void build(int y, int &x, int l, int r, int val)
{
    x = ++tot;
    tr[x] = tr[y];
    ++tr[x].num;
    tr[x].sum += d[val];
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (val <= mid)
        build(tr[y].l, tr[x].l, l, mid, val);
    else
        build(tr[y].r, tr[x].r, mid + 1, r, val);
    return;
}
ll query(int x, int y, int l, int r, int val)
{
    if (l == r)
        return l;
    int k = tr[tr[y].l].num - tr[tr[x].l].num;
    int mid = (l + r) >> 1;
    if (val <= k)
        return query(tr[x].l, tr[y].l, l, mid, val);
    else
        return query(tr[x].r, tr[y].r, mid + 1, r, val - k);
}
ll ask(int x, int y, int L, int R, int l, int r, int val)
{
    if (L == l && R == r)
        return abs(tr[y].sum - tr[x].sum - (ll)(tr[y].num - tr[x].num) * d[val]);
    int mid = (L + R) >> 1;
    if (r <= mid)
        return ask(tr[x].l, tr[y].l, L, mid, l, r, val);
    if (l >= mid + 1)
        return ask(tr[x].r, tr[y].r, mid + 1, R, l, r, val);
    return ask(tr[x].l, tr[y].l, L, mid, l, mid, val) + ask(tr[x].r, tr[y].r, mid + 1, R, mid + 1, r, val);
}
int main()
{
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; ++i)
    {
        char p, q;
        scanf(" %c%d %c%d", &p, &s[i], &q, &t[i]);
        if (s[i] > t[i])
            swap(s[i], t[i]);
        if (p != q)
        {
            vis[i] = 1;
            d[++cnt] = s[i];
            d[++cnt] = t[i];
        }
        else
            ans += t[i] - s[i];
    }
    sort(d + 1, d + cnt + 1);
    if (k == 1)
    {
        int w = d[cnt / 2 + 1];
        for (int i = 1; i <= n; ++i)
            if (vis[i])
                ans += abs(s[i] - w) + abs(t[i] - w) + 1;
        printf("%lld", ans);
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        if (vis[i])
        {
            ++sum;
            w[sum].x = s[i];
            w[sum].y = t[i];
            w[sum].num = s[i] + t[i];
        }
    sort(w + 1, w + sum + 1, cmp);
    int len = unique(d + 1, d + cnt + 1) - d - 1;
    for (int i = 1; i <= sum; ++i)
    {
        w[i].x = lower_bound(d + 1, d + len + 1, w[i].x) - d;
        w[i].y = lower_bound(d + 1, d + len + 1, w[i].y) - d;
        build(rt[i - 1], rt[i], 1, len, w[i].x);
        build(rt[i], rt[i], 1, len, w[i].y);
    }
    ll minx = -1;
    for (int i = 1; i < sum; ++i)
    {
        int num1 = tr[rt[i]].num, num2 = tr[rt[sum]].num - tr[rt[i]].num;
        int w1 = query(rt[0], rt[i], 1, len, num1 / 2 + 1);
        int w2 = query(rt[i], rt[sum], 1, len, num2 / 2 + 1);
        ll tmp = 0;
        tmp += ask(rt[0], rt[i], 1, len, 1, w1, w1);
        if (w1 + 1 <= len)
            tmp += ask(rt[0], rt[i], 1, len, w1 + 1, len, w1);
        tmp += ask(rt[i], rt[sum], 1, len, 1, w2, w2);
        if (w2 + 1 <= len)
            tmp += ask(rt[i], rt[sum], 1, len, w2 + 1, len, w2);
        if (minx == -1 || tmp < minx)
            minx = tmp;
    }
    if (!sum)
        minx = 0;
    ans = ans + minx + sum;
    printf("%lld", ans);
    return 0;
}