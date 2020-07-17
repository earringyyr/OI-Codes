#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int t, n;
long long c[50005], sum[50005];
struct node
{
    int a;
    int b;
} a[50005];
bool cmp(node aa, node bb)
{
    if (min(aa.a, bb.b) == min(bb.a, aa.b))
        return aa.a < bb.a;
    return min(aa.a, bb.b) < min(bb.a, aa.b);
}
int main()
{
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &a[i].a, &a[i].b);
        sort(a + 1, a + n + 1, cmp);
        for (int i = 1; i <= n; ++i)
        {
            sum[i] = sum[i - 1] + a[i].a;
            c[i] = max(c[i - 1], sum[i]) + a[i].b;
        }
        printf("%lld\n", c[n]);
    }
    return 0;
}