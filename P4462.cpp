#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
int n, m, len, k, num, a[100005], ans[100005], c[1000005];
struct node
{
    int id;
    int l;
    int r;
} q[100005];
bool cmp(node aa, node bb)
{
    if (aa.r / len == bb.r / len)
    {
        if ((aa.r / len) % 2 == 0)
            return aa.l < bb.l;
        else
            return aa.l > bb.l;
    }
    return aa.r < bb.r;
}
void add(int x)
{
    num += c[a[x] ^ k];
    ++c[a[x]];
    return;
}
void del(int x)
{
    --c[a[x]];
    num -= c[a[x] ^ k];
    return;
}
signed main()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 2; i <= n + 1; ++i)
    {
        scanf("%lld", &a[i]);
        a[i] ^= a[i - 1];
    }
    for (int i = 1; i <= m; ++i)
    {
        q[i].id = i;
        scanf("%lld%lld", &q[i].l, &q[i].r);
        ++q[i].r;
    }
    len = sqrt(n + 1);
    sort(q + 1, q + m + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i)
    {
        while (l > q[i].l)
            add(--l);
        while (r < q[i].r)
            add(++r);
        while (l < q[i].l)
            del(l++);
        while (r > q[i].r)
            del(r--);
        ans[q[i].id] = num;
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}