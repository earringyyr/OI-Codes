#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n, m, len, l = 1, r, c[50005];
long long k, cnt[50005], ans[50005][2];
struct node
{
    int id;
    int l;
    int r;
} a[50005];
bool cmp(node aa, node bb)
{
    if ((aa.r - 1) / len == (bb.r - 1) / len)
    {
        if (aa.l < bb.l)
            return true;
        if (aa.l > bb.l)
            return false;
        if (aa.r < bb.r)
            return true;
        return false;
    }
    else
    {
        if (aa.r < bb.r)
            return true;
        if (aa.r > bb.r)
            return false;
        if (aa.l < bb.l)
            return true;
        return false;
    }
}
long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
void add(int id)
{
    k += 2 * cnt[c[id]];
    ++cnt[c[id]];
    return;
}
void del(int id)
{
    --cnt[c[id]];
    k -= 2 * cnt[c[id]];
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i <= m; ++i)
    {
        a[i].id = i;
        scanf("%d%d", &a[i].l, &a[i].r);
    }
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        while (l < a[i].l)
            del(l++);
        while (l > a[i].l)
            add(--l);
        while (r < a[i].r)
            add(++r);
        while (r > a[i].r)
            del(r--);
        ans[a[i].id][0] = k;
        ans[a[i].id][1] = (long long)(a[i].r - a[i].l + 1) * (a[i].r - a[i].l);
    }
    for (int i = 1; i <= m; ++i)
        if (!ans[i][0] || !ans[i][1])
            puts("0/1");
        else
        {
            long long x = gcd(ans[i][0], ans[i][1]);
            ans[i][0] /= x;
            ans[i][1] /= x;
            printf("%lld/%lld\n", ans[i][0], ans[i][1]);
        }
    return 0;
}