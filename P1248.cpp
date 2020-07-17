#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
long long c[50005], sum[50005];
struct node
{
    int id;
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
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i].a);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i].b);
    for (int i = 1; i <= n; ++i)
        a[i].id = i;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + a[i].a;
        c[i] = max(c[i - 1], sum[i]) + a[i].b;
    }
    printf("%lld\n", c[n]);
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i].id);
    return 0;
}