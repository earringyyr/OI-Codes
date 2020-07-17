#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define int long long
using namespace std;
int n, q, len, num, a[100005], f[100005], g[100005];
int lg[100005], que[100005], ans[100005];
int pre[100005], suf[100005], st[100005][20];
struct node
{
    int id;
    int l;
    int r;
} s[100005];
bool cmp(node aa, node bb)
{
    if ((aa.l - 1) / len == (bb.l - 1) / len)
    {
        if (aa.r != bb.r)
        {
            if ((aa.l - 1) / len % 2 == 0)
                return aa.r < bb.r;
            return aa.r > bb.r;
        }
        return aa.l < bb.l;
    }
    return aa.l < bb.l;
}
int ask(int x, int y)
{
    if (a[x] < a[y])
        return x;
    return y;
}
int lef(int l, int r)
{
    int pos = ask(st[l][lg[r - l + 1]], st[r - (1 << (lg[r - l + 1])) + 1][lg[r - l + 1]]);
    return a[pos] * (r - pos + 1) + g[l] - g[pos];
}
int rig(int l, int r)
{
    int pos = ask(st[l][lg[r - l + 1]], st[r - (1 << (lg[r - l + 1])) + 1][lg[r - l + 1]]);
    return a[pos] * (pos - l + 1) + f[r] - f[pos];
}
signed main()
{
    scanf("%lld%lld", &n, &q);
    len = sqrt(n);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        st[i][0] = i;
    }
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= lg[n - i + 1]; ++j)
            st[i][j] = ask(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    int head, tail;
    head = 1;
    tail = 0;
    que[++tail] = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (head < tail && a[que[tail]] >= a[i])
            --tail;
        pre[i] = que[tail];
        que[++tail] = i;
    }
    head = 1;
    tail = 0;
    que[++tail] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        while (head < tail && a[que[tail]] >= a[i])
            --tail;
        suf[i] = que[tail];
        que[++tail] = i;
    }
    for (int i = 1; i <= n; ++i)
        f[i] = a[i] * (i - pre[i]) + f[pre[i]];
    for (int i = n; i >= 1; --i)
        g[i] = a[i] * (suf[i] - i) + g[suf[i]];
    for (int i = 1; i <= q; ++i)
    {
        s[i].id = i;
        scanf("%lld%lld", &s[i].l, &s[i].r);
    }
    sort(s + 1, s + q + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= q; ++i)
    {
        while (l > s[i].l)
        {
            --l;
            num += lef(l, r);
        }
        while (r < s[i].r)
        {
            ++r;
            num += rig(l, r);
        }
        while (r > s[i].r)
        {
            num -= rig(l, r);
            --r;
        }
        while (l < s[i].l)
        {
            num -= lef(l, r);
            ++l;
        }
        ans[s[i].id] = num;
    }
    for (int i = 1; i <= q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}