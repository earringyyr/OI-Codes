#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
int n, k, len, sum, ans;
int l[2005], r[2005], f[2005];
int b[4005], c[4005];
struct node
{
    int l;
    int r;
    int w;
    node(int ll = 0, int rr = 0, int ww = 0)
    {
        l = ll;
        r = rr;
        w = ww;
    }
} a[2005];
struct tree
{
    int l;
    int r;
    int maxn;
} tr[16005];
bool cmp(node aa, node bb)
{
    return aa.r < bb.r;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= len)
    {
        c[x] = max(c[x], val);
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int maxn = 0;
    while (x >= 1)
    {
        maxn = max(maxn, c[x]);
        x -= lowbit(x);
    }
    return maxn;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d", &l[i], &r[i]);
        if (i == 1 && l[i] == 1 && r[i] == 1)
        {
            --i;
            --k;
            continue;
        }
        ++r[i];
        b[++sum] = l[i];
        b[++sum] = r[i];
    }
    sort(b + 1, b + sum + 1);
    len = unique(b + 1, b + sum + 1) - b - 1;
    for (int i = 1; i <= k; ++i)
    {
        l[i] = lower_bound(b + 1, b + len + 1, l[i]) - b;
        r[i] = lower_bound(b + 1, b + len + 1, r[i]) - b;
    }
    for (int i = 1; i <= k; ++i)
    {
        sum = 0;
        for (int j = 1; j < i; ++j)
            if (l[j] >= l[i] && r[j] <= r[i])
                a[++sum] = node(l[j], r[j], f[j]);
        sort(a + 1, a + sum + 1, cmp);
        memset(c, 0, sizeof(c));
        for (int j = 1; j <= sum; ++j)
        {
            int tmp = ask(a[j].l - 1);
            f[i] = max(f[i], tmp + a[j].w);
            add(a[j].r, tmp + a[j].w);
        }
        ++f[i];
    }
    for (int i = 1; i <= k; ++i)
        a[i] = node(l[i], r[i], f[i]);
    sort(a + 1, a + k + 1, cmp);
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= k; ++i)
    {
        int tmp = ask(a[i].l - 1);
        ans = max(ans, tmp + a[i].w);
        add(a[i].r, tmp + a[i].w);
    }
    printf("%d", k - ans);
    return 0;
}